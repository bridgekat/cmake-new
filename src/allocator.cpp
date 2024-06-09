module;
#include <memory>
#include <utility>
#include <vector>

export module allocator;
export namespace allocator {

//! A simple region-based memory allocator (uses larger blocks than `std::deque`).
//! This ensures the allocated objects to stay in the same place, like in `std::deque`.
template <typename T>
class Allocator {
public:
  static constexpr std::size_t DEFAULT_BLOCK_SIZE = 1024uz;

  Allocator(std::size_t block_size = DEFAULT_BLOCK_SIZE):
      _block_size(block_size) {}

  ~Allocator() noexcept {
    _deallocate();
  }

  Allocator(Allocator const&) = delete;
  Allocator(Allocator&& r) noexcept:
      _alloc(std::move(r._alloc)),
      _block_size(r._block_size),
      _blocks(std::move(r._blocks)),
      _next(r._next) {}

  auto operator=(Allocator const&) -> Allocator& = delete;
  auto operator=(Allocator&& r) noexcept -> Allocator& {
    swap(*this, r);
    return *this;
  }

  friend void swap(Allocator& l, Allocator& r) noexcept {
    using std::swap;
    swap(l._alloc, r._alloc);
    swap(l._block_size, r._block_size);
    swap(l._blocks, r._blocks);
    swap(l._next, r._next);
  }

  //! Constructs new object with arguments passed to a constructor of `T`.
  template <typename... Ts>
  auto emplace(Ts&&... args) -> T* {
    if (_next == 0)
      _blocks.push_back(_alloc.allocate(_block_size));
    auto const res = _blocks.back() + _next;
    std::construct_at(res, std::forward<Ts>(args)...);
    _next++;
    if (_next >= _block_size)
      _next = 0;
    return res;
  }

  //! Destructs all objects.
  void clear() {
    _deallocate();
    _blocks.clear();
    _next = 0;
  }

  //! Returns the number of allocated objects.
  auto size() const -> std::size_t {
    if (_next == 0)
      return _block_size * _blocks.size();
    return _block_size * (_blocks.size() - 1) + _next;
  }

private:
  std::allocator<T> _alloc;
  std::size_t _block_size;
  std::vector<T*> _blocks;
  std::size_t _next = 0;

  void _deallocate() {
    for (auto i = 0uz; i < _blocks.size(); i++) {
      std::destroy_n(_blocks[i], (i + 1 == _blocks.size() && _next > 0) ? _next : _block_size);
      _alloc.deallocate(_blocks[i], _block_size);
    }
  }
};

}

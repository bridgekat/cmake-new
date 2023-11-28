module;
#include <print>
#include <string>

export module the_project_name;

export class Greeter {
public:
  enum class Language { CN, DE, EN, ES, FR };

  explicit Greeter(std::string name):
      name(std::move(name)) {}

  void greet(Language lang = Language::EN) const {
    switch (lang) {
      case Language::CN:
        std::println("你好，{}！", name);
        break;
      case Language::DE:
        std::println("Hallo {}!", name);
        break;
      case Language::EN:
        std::println("Hello, {}!", name);
        break;
      case Language::ES:
        std::println("¡Hola {}!", name);
        break;
      case Language::FR:
        std::println("Bonjour {}!", name);
        break;
    }
  }

private:
  std::string name;
};

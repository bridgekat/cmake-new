import the_project_name;

auto main() -> int {
  auto greeter = Greeter("world");
  greeter.greet(Greeter::Language::EN);
  return 0;
}

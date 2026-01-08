#include <format>          // Requires C++20 or later for std::format
#include <source_location> // Requires C++20 or later
#include <stdexcept>
#include <string>

// Define a custom exception for unimplemented functionality
class NotImplementedException : public std::logic_error {
public:
  // Constructor using std::format and std::source_location (C++20 style)
  NotImplementedException(
      const std::string &message = "Functionality not yet implemented!",
      const std::source_location location = std::source_location::current())
      : std::logic_error{std::format("{}: {} is not implemented!",
                                     location.file_name(),
                                     location.function_name(), message)} {}

  // A simpler constructor for older C++ versions
  NotImplementedException(const char *message) : std::logic_error(message) {}
};

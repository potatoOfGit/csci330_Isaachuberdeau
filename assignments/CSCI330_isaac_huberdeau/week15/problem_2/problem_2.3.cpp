#include <iostream>
#include <map>
#include <regex>
#include <string>

class TemplateEngine {
 private:
  std::map<std::string, std::string> variables;

 public:
  void set_variable(const std::string& name, const std::string& value) {
    variables[name] = value;
  }

  std::string render(const std::string& template_text) {
    // TODO: Replace {{variable_name}} with values
    // Example: "Hello {{name}}!" with name="World" -> "Hello World!"

    std::string result = template_text;
    std::regex pattern(R"(\{\{([a-zA-Z_][a-zA-Z0-9_]*)\}\})");
    std::smatch match;

    std::string temp = result;
    while (std::regex_search(temp, match, pattern)) {
      std::string var_name = match[1].str();
      std::string replacement = "";

      // Check if variable exists
      if (variables.find(var_name) != variables.end()) {
        replacement = variables[var_name];
      }

      // Replace in result
      size_t pos = result.find("{{" + var_name + "}}");
      if (pos != std::string::npos) {
        result.replace(pos, var_name.length() + 4, replacement);
      }

      // Update temp for next iteration
      temp = result;
    }

    return result;
  }

  std::string render_with_conditionals(const std::string& template_text) {
    // TODO: Handle simple conditionals
    // {{#if variable_name}}text{{/if}} - show text if variable exists and is
    // not empty
    // {{#unless variable_name}}text{{/unless}} - show text if variable doesn't
    // exist or is empty

    std::string result = template_text;

    // Handle {{#if variable}}...{{/if}}
    std::regex if_pattern(
        R"(\{\{#if ([a-zA-Z_][a-zA-Z0-9_]*)\}\}(.*?)\{\{/if\}\})");
    std::smatch match;

    while (std::regex_search(result, match, if_pattern)) {
      std::string var_name = match[1].str();
      std::string content = match[2].str();
      std::string replacement = "";

      // Show content if variable exists and is not empty
      if (variables.find(var_name) != variables.end() &&
          !variables[var_name].empty()) {
        replacement = content;
      }

      result = std::regex_replace(result, if_pattern, replacement,
                                  std::regex_constants::format_first_only);
    }

    // Handle {{#unless variable}}...{{/unless}}
    std::regex unless_pattern(
        R"(\{\{#unless ([a-zA-Z_][a-zA-Z0-9_]*)\}\}(.*?)\{\{/unless\}\})");

    while (std::regex_search(result, match, unless_pattern)) {
      std::string var_name = match[1].str();
      std::string content = match[2].str();
      std::string replacement = "";

      // Show content if variable doesn't exist or is empty
      if (variables.find(var_name) == variables.end() ||
          variables[var_name].empty()) {
        replacement = content;
      }

      result = std::regex_replace(result, unless_pattern, replacement,
                                  std::regex_constants::format_first_only);
    }

    // Now render regular variables
    result = render(result);

    return result;
  }
};

int main() {
  TemplateEngine engine;
  engine.set_variable("name", "Alice");
  engine.set_variable("age", "25");
  engine.set_variable("city", "New York");

  std::string basic_template =
      "Hello {{name}}! You are {{age}} years old and live in {{city}}.";
  std::cout << engine.render(basic_template) << std::endl;

  std::string conditional_template =
      "Welcome {{name}}! "
      "{{#if age}}You are {{age}} years old. {{/if}}"
      "{{#unless phone}}Please provide your phone number. {{/unless}}";

  std::cout << engine.render_with_conditionals(conditional_template)
            << std::endl;

  return 0;
}
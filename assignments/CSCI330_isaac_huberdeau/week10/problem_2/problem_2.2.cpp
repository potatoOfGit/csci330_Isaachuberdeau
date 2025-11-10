#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

class ExpensiveResource {
 private:
  std::string id;
  int creation_cost;

 public:
  ExpensiveResource(const std::string& resource_id)
      : id(resource_id), creation_cost(100) {
    std::cout << "Creating expensive resource: " << id
              << " (cost: " << creation_cost << ")" << std::endl;
  }

  ~ExpensiveResource() {
    std::cout << "Destroying resource: " << id << std::endl;
  }

  const std::string& get_id() const { return id; }
  void use() const { std::cout << "Using resource: " << id << std::endl; }
};

class ResourceCache {
 private:
  std::unordered_map<std::string, std::weak_ptr<ExpensiveResource>> cache;

 public:
  std::shared_ptr<ExpensiveResource> get_resource(const std::string& id) {
    auto it = cache.find(id);
    if (it != cache.end()) {
      auto shared = it->second.lock();
      if (shared) {
        std::cout << "Reusing cached resource: " << id << std::endl;
        return shared;
      }
    }

    auto new_resource = std::make_shared<ExpensiveResource>(id);
    cache[id] = new_resource;
    return new_resource;
  }

  void show_cache_status() const {
    std::cout << "Cache contains " << cache.size() << " entries:" << std::endl;
    for (const auto& pair : cache) {
      std::cout << "  " << pair.first << ": "
                << (pair.second.expired() ? "expired" : "active") << std::endl;
    }
  }

  void cleanup_expired() {
    for (auto it = cache.begin(); it != cache.end();) {
      if (it->second.expired()) {
        std::cout << "Removing expired entry: " << it->first << std::endl;
        it = cache.erase(it);
      } else {
        ++it;
      }
    }
  }
};

int main() {
  ResourceCache cache;

  std::cout << "=== Test 1: Creating and sharing resources ===\n";
  {
    auto resource1 = cache.get_resource("res1");
    auto resource2 = cache.get_resource("res2");
    auto resource1_again = cache.get_resource("res1");

    std::cout << "resource1 and resource1_again are same object: "
              << (resource1.get() == resource1_again.get()) << std::endl;

    resource1->use();
    resource2->use();
    resource1_again->use();

    cache.show_cache_status();
  }

  std::cout << "\n=== Test 2: Resources destroyed, cache cleanup ===\n";
  cache.show_cache_status();
  cache.cleanup_expired();
  cache.show_cache_status();

  std::cout << "\n=== Test 3: Creating resources after cleanup ===\n";
  auto resource3 = cache.get_resource("res1");
  cache.show_cache_status();

  return 0;
}
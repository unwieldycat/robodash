#include <map>
#include <optional>
#include <string>
#include <variant>

namespace rd {
namespace util {

/**
 * Variant of possible value types.
 *
 * Allowed types: `bool`, `char`, `double`, `int`, `std::string`
 */
using VType = std::variant<bool, int, double, char, std::string>;

/**
 * Proprietary lightweight persistent key-value storage utility. Requires an SD card.
 */
class KVStore {
  public:
	/**
	 * Create a new KVStore
	 *
	 * @param file
	 */
	KVStore(std::string file);

	/**
	 * Set a value
	 *
	 * @param key Key name
	 * @param value Value
	 */
	void set(std::string key, VType value);

	/**
	 * Get a value
	 *
	 * @param key Key name
	 * @return Optional value of varying type
	 */
	std::optional<VType> get(std::string key);

	/**
	 * Get a value of a certain type
	 *
	 * @tparam Type of value
	 * @param key Key name
	 * @return Optional value of type T
	 */
	template <typename T> std::optional<T> get(std::string key) {
		static_assert(ValidVType<T>::value, "Invalid type");
		std::map<std::string, VType>::iterator iter = data.find(key);
		if (iter != data.end()) {
			T *value = std::get_if<T>(&iter->second);
			if (value != nullptr) return *value;
		}
		return std::nullopt;
	}

	/**
	 * Ensure that a value is initialized
	 *
	 * Gets the value of the given type at the provided key. If the value is not set or not of the
	 * same type, the provided default value will be set.
	 *
	 * @tparam Type of value
	 * @param key Key name
	 * @param default_value Value to set if not found
	 * @return Value of type T
	 */
	template <typename T> T ensure(std::string key, T default_value) {
		static_assert(ValidVType<T>::value, "Invalid type");
		std::map<std::string, VType>::iterator iter = data.find(key);
		if (iter != data.end()) {
			T *value = std::get_if<T>(&iter->second);
			if (value != nullptr) return *value;
		}
		set(key, default_value);
		return default_value;
	}

  private:
	void load();
	std::optional<std::pair<std::string, std::string>> parse_line(std::string line);
	std::optional<VType> parse_value(std::string value);

	template <typename T>
	using ValidVType = typename std::disjunction<
	    std::is_same<std::string, T>, std::is_same<char, T>, std::is_same<int, T>,
	    std::is_same<double, T>, std::is_same<bool, T>>::type;

	std::string file_path;
	std::map<std::string, VType> data;
};

} // namespace util
} // namespace rd
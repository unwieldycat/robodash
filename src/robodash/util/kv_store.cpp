#pragma once
#include "robodash/util/kv_store.hpp"
#include "robodash/detail/platform.h"
#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <optional>
#include <sstream>

// ================================ Helpers ================================ //

bool is_whitespace(char s) { return s == ' ' || s == '	'; };
bool may_be_integer(char s) { return std::isdigit(s) || s == '-'; }
bool may_be_float(char s) {
	return std::isdigit(s) || s == '-' || s == '.' || s == '+' || s == 'e';
}

struct ConversionVisitor {
	std::string operator()(std::string &v) { return "\"" + v + "\""; }
	std::string operator()(int v) { return std::to_string(v); }
	std::string operator()(double v) { return std::to_string(v); }
	std::string operator()(char v) { return "'" + std::string(1, v) + "'"; }
	std::string operator()(bool v) { return (v) ? "true" : "false"; }
};

// ========================= KVStore Implementation ========================= //

rd::util::KVStore::KVStore() {}

void rd::util::KVStore::set(std::string key, rd::util::VType value) { data.emplace(key, value); }

std::optional<rd::util::VType> rd::util::KVStore::get(std::string key) {
	std::map<std::string, VType>::iterator iter = data.find(key);
	if (iter == data.end()) return std::nullopt;
	return iter->second;
}

void rd::util::KVStore::read(std::string file_path) {
	if (!rd::detail::platform::sd_installed()) {
		return;
	}

	std::fstream file(file_path, std::ios::in);

	if (!file.is_open()) {
		return;
	}

	std::string line;

	while (std::getline(file, line)) {
		std::optional<std::pair<std::string, std::string>> parsed_line = parse_line(line);
		if (!parsed_line.has_value()) continue;
		std::string key = parsed_line.value().first;
		std::string str_value = parsed_line.value().second;

		std::optional<VType> value = parse_value(str_value);
		if (!value.has_value()) continue;
		data.emplace(key, value.value());
	}
}

void rd::util::KVStore::write(std::string file_path) {
	if (!rd::detail::platform::sd_installed()) {
		return;
	}

	std::fstream file_out(file_path, std::ios::out | std::ios::trunc);

	if (!file_out.is_open()) {
		return;
	}

	for (auto &[key, value] : data) {
		file_out << key << ": " << std::visit(ConversionVisitor(), value) << std::endl;
	}

	file_out.close();
}

std::optional<std::pair<std::string, std::string>> rd::util::KVStore::parse_line(std::string line) {
	std::string::iterator first_char = std::find_if_not(line.begin(), line.end(), is_whitespace);
	if (*first_char == '#') return std::nullopt;

	std::string::iterator delimiter = std::find(first_char, line.end(), ':');
	if (delimiter == line.end()) return std::nullopt;

	std::string::iterator value_start = std::find_if_not(delimiter + 1, line.end(), is_whitespace);

	std::string key(first_char, delimiter);
	std::string str_value(value_start, line.end());

	return std::make_pair(key, str_value);
}

std::optional<rd::util::VType> rd::util::KVStore::parse_value(std::string value) {
	// bool
	if (value == "true" || value == "false") {
		return value == "true";
	}

	// int & float
	if (std::find_if_not(value.begin(), value.end(), may_be_integer) == value.end()) {
		try {
			return std::stoi(value);
		} catch (std::invalid_argument err) {
			return std::nullopt;
		}
	} else if (std::find_if_not(value.begin(), value.end(), may_be_float) == value.end()) {
		try {
			return std::stod(value);
		} catch (std::invalid_argument err) {
			return std::nullopt;
		}
	}

	// string
	if (value.starts_with('"') && value.ends_with('"')) {
		std::string::iterator open_quote = std::find(value.begin(), value.end(), '"');
		std::string::iterator close_quote = std::find(next(open_quote), value.end(), '"');
		return std::string(open_quote + 1, close_quote);
	}

	// char
	if (value.length() == 3 && value.starts_with('\'') && value.ends_with('\'')) {
		return value.at(1);
	}

	return std::nullopt;
}

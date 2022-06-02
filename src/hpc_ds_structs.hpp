#pragma once
#include <array>
#include <cassert>
#include <fmt/core.h>
#include <i3d/image3d.h>
#include <i3d/vector3d.h>
#include <map>
#include <optional>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

namespace datastore {

namespace details {
template <typename key_t, typename value_t>
std::ostream& operator<<(std::ostream& stream,
                         const std::map<key_t, value_t>& map) {
	stream << "{\n";

	for (const auto& [k, v] : map) {
		stream << k << ": " << v << '\n';
	}
	stream << "}\n";
	return stream;
}

template <typename T>
std::string vec_to_string(const std::vector<T>& vec) {
	std::stringstream ss;
	ss << "[";
	const char* delim = "";
	for (auto& v : vec) {
		ss << delim << v;
		delim = ", ";
	}

	ss << "]";
	return ss.str();
}

template <typename T>
std::string vec_to_string(const i3d::Vector3d<T>& vec) {
	return fmt::format("[{}, {}, {}]", vec.x, vec.y, vec.z);
}
} // namespace details

template <typename T>
concept Scalar = requires(T) {
	requires std::is_scalar_v<T>;
};

template <typename T>
concept Basic = requires(T) {
	requires Scalar<T> || std::is_same_v<T, std::string>;
};

template <typename T>
concept Vector_cnpt = requires(T) {
	requires std::is_same_v<std::vector<typename T::value_type>, T>;
};

template <typename T>
concept Optional_cnpt = requires(T) {
	requires std::is_same_v<std::optional<typename T::value_type>, T>;
};

template <typename T>
concept Vector3d_cnpt = requires(T a) {
	requires std::is_same_v<i3d::Vector3d<decltype(a.x)>, T>;
	requires Basic<decltype(a.x)>;
};

class DatasetProperties {
  public:
	std::string uuid;
	std::string voxel_type;
	i3d::Vector3d<int> dimensions;
	int channels;
	int angles;
	std::optional<std::string> transformations;
	std::string voxel_unit;
	std::optional<i3d::Vector3d<double>> voxel_resolution;
	std::optional<i3d::Vector3d<double>> timepoint_resolution;
	std::optional<i3d::Vector3d<double>> channel_resolution;
	std::optional<i3d::Vector3d<double>> angle_resolution;
	std::string compression;
	std::vector<std::map<std::string, i3d::Vector3d<int>>> resolution_levels;
	std::vector<int> versions;
	std::string label;
	std::optional<std::string> view_registrations;
	std::vector<int> timepoint_ids;

	operator std::string() const {
		std::stringstream ss;

		ss << "UUID: " << uuid << '\n';
		ss << "voxelType: " << voxel_type << '\n';
		ss << "dimensions: " << details::vec_to_string(dimensions) << '\n';
		ss << "channels: " << channels << '\n';
		ss << "angles: " << angles << '\n';
		ss << "transformations: " << transformations.value_or("null") << '\n';
		ss << "voxelUnit: " << voxel_unit << '\n';
		ss << "voxelResolution: "
		   << (voxel_resolution
		           ? details::vec_to_string(voxel_resolution.value())
		           : "null")
		   << '\n';
		ss << "timepointResolution: "
		   << (timepoint_resolution
		           ? details::vec_to_string(timepoint_resolution.value())
		           : "null")
		   << '\n';

		ss << "channelResolution: "
		   << (channel_resolution
		           ? details::vec_to_string(channel_resolution.value())
		           : "null")
		   << '\n';

		ss << "angleResolution: "
		   << (angle_resolution
		           ? details::vec_to_string(angle_resolution.value())
		           : "null")
		   << '\n';

		ss << "compression: " << compression << '\n';
		ss << "resolutionLevels: " << details::vec_to_string(resolution_levels)
		   << '\n';
		ss << "versions: " << details::vec_to_string(versions) << '\n';
		ss << "label: " << label << '\n';
		ss << "viewRegistrations: " << view_registrations.value_or("null")
		   << '\n';
		ss << "timepointIds: " << details::vec_to_string(timepoint_ids) << '\n';

		return ss.str();
	}
};
} // namespace datastore

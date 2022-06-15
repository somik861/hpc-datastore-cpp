#pragma once
#include "hpc_ds_details.hpp"
#include "hpc_ds_structs.hpp"
#include <fmt/core.h>
#include <i3d/image3d.h>
#include <string>
#include <type_traits>
#include <vector>

namespace datastore {
inline DatasetProperties get_dataset_properties(const std::string& ip,
                                                int port,
                                                const std::string& uuid);

// TODO docs
template <cnpts::Scalar T>
i3d::Image3d<T> read_image(const std::string& ip,
                           int port,
                           const std::string& uuid,
                           int channel = 0,
                           int timepoint = 0,
                           int angle = 0,
                           i3d::Vector3d<int> resolution = {1, 1, 1},
                           const std::string& version = "latest");

// TODO docs
template <cnpts::Scalar T>
bool write_image(const i3d::Image3d<T>& img,
                 const std::string& ip,
                 int port,
                 const std::string& uuid,
                 int channel = 0,
                 int timepoint = 0,
                 int angle = 0,
                 i3d::Vector3d<int> resolution = {1, 1, 1},
                 const std::string version = "latest");

class ImageView {
  public:
	ImageView(std::string ip,
	          int port,
	          std::string uuid,
	          int channel,
	          int timepoint,
	          int angle,
	          i3d::Vector3d<int> resolution,
	          std::string version);

	// TODO docs
	template <cnpts::Scalar T>
	i3d::Image3d<T> read_block(i3d::Vector3d<int> coord) const;

	// TODO docs
	template <cnpts::Scalar T>
	bool read_block(i3d::Vector3d<int> coord,
	                i3d::Image3d<T>& dest,
	                i3d::Vector3d<int> dest_offset = {0, 0, 0}) const;
	// TODO docs
	template <cnpts::Scalar T>
	std::vector<i3d::Image3d<T>>
	read_blocks(const std::vector<i3d::Vector3d<int>>& coords) const;

	// TODO docs
	template <cnpts::Scalar T>
	bool read_blocks(const std::vector<i3d::Vector3d<int>>& coords,
	                 i3d::Image3d<T>& dest,
	                 const std::vector<i3d::Vector3d<int>>& offsets) const;

	// TODO docs
	template <cnpts::Scalar T>
	i3d::Image3d<T> read_image() const;

	// TODO docs
	template <cnpts::Scalar T>
	bool write_block(const i3d::Image3d<T>& src,
	                 i3d::Vector3d<int> coord,
	                 i3d::Vector3d<int> src_offset = {0, 0, 0}) const;
	// TODO docs
	template <cnpts::Scalar T>
	bool write_blocks(const i3d::Image3d<T>& src,
	                  const std::vector<i3d::Vector3d<int>>& coords,
	                  const std::vector<i3d::Vector3d<int>>& src_offsets) const;
	// TODO docs
	template <cnpts::Scalar T>
	bool write_image(const i3d::Image3d<T>& img) const;

  private:
	std::string _ip;
	int _port;
	std::string _uuid;
	int _channel;
	int _timepoint;
	int _angle;
	i3d::Vector3d<int> _resolution;
	std::string _version;
};

class Connection {
  public:
	// TODO docs
	Connection(std::string ip, int port, std::string uuid);
	// TODO docs
	ImageView get_view(int channel,
	                   int timepoint,
	                   int angle,
	                   i3d::Vector3d<int> resolution,
	                   const std::string& version) const;
	// TODO docs
	template <cnpts::Scalar T>
	i3d::Image3d<T> read_block(i3d::Vector3d<int> coord,
	                           int channel,
	                           int timepoint,
	                           int angle,
	                           i3d::Vector3d<int> resolution,
	                           const std::string& version) const;
	// TODO docs
	template <cnpts::Scalar T>
	bool read_block(i3d::Vector3d<int> coord,
	                i3d::Image3d<T>& dest,
	                i3d::Vector3d<int> dest_offset,
	                int channel,
	                int timepoint,
	                int angle,
	                i3d::Vector3d<int> resolution,
	                const std::string& version) const;
	// TODO docs
	template <cnpts::Scalar T>
	std::vector<i3d::Image3d<T>>
	read_blocks(const std::vector<i3d::Vector3d<int>>& coords,
	            int channel,
	            int timepoint,
	            int angle,
	            i3d::Vector3d<int> resolution,
	            const std::string& version) const;
	// TODO docs
	template <cnpts::Scalar T>
	bool read_blocks(const std::vector<i3d::Vector3d<int>>& coords,
	                 i3d::Image3d<T>& dest,
	                 const std::vector<i3d::Vector3d<int>>& dest_offsets,
	                 int channel,
	                 int timepoint,
	                 int angle,
	                 i3d::Vector3d<int> resolution,
	                 const std::string& version) const;
	// TODO docs
	template <cnpts::Scalar T>
	i3d::Image3d<T> read_image(int channel,
	                           int timepoint,
	                           int angle,
	                           i3d::Vector3d<int> resolution,
	                           const std::string& version) const;
	// TODO docs
	template <cnpts::Scalar T>
	bool write_block(const i3d::Image3d<T>& src,
	                 i3d::Vector3d<int> coord,
	                 i3d::Vector3d<int> src_offset,
	                 int channel,
	                 int timepoint,
	                 int angle,
	                 i3d::Vector3d<int> resolution,
	                 const std::string& version) const;
	// TODO docs
	template <cnpts::Scalar T>
	bool write_blocks(const i3d::Image3d<T>& src,
	                  const std::vector<i3d::Vector3d<int>>& coords,
	                  const std::vector<i3d::Vector3d<int>>& src_offsets,
	                  int channel,
	                  int timepoint,
	                  int angle,
	                  i3d::Vector3d<int> resolution,
	                  const std::string& version) const;
	// TODO docs
	template <cnpts::Scalar T>
	bool write_image(const i3d::Image3d<T>& src,
	                 int channel,
	                 int timepoint,
	                 int angle,
	                 i3d::Vector3d<int> resolution,
	                 const std::string& version) const;

  private:
	std::string _ip;
	int _port;
	std::string _uuid;
};

} // namespace datastore

/* ================= IMPLEMENTATION FOLLOWS ======================== */

namespace datastore {
/* ===================================== Global space */
/* inline */ DatasetProperties get_dataset_properties(const std::string& ip,
                                                      int port,
                                                      const std::string& uuid) {
	std::string dataset_url = details::get_dataset_url(ip, port, uuid);
	return details::get_dataset_properties(dataset_url);
}

template <cnpts::Scalar T>
i3d::Image3d<T> read_image(const std::string& ip,
                           int port,
                           const std::string& uuid,
                           int channel /* = 0 */,
                           int timepoint /*  = 0 */,
                           int angle /* = 0 */,
                           i3d::Vector3d<int> resolution /* = {1, 1, 1} */,
                           const std::string& version /* = "latest" */) {
	return ImageView(ip, port, uuid, channel, timepoint, angle, resolution,
	                 version)
	    .read_image<T>();
}

template <cnpts::Scalar T>
bool write_image(const i3d::Image3d<T>& img,
                 const std::string& ip,
                 int port,
                 const std::string& uuid,
                 int channel /* = 0 */,
                 int timepoint /* = 0 */,
                 int angle /* = 0 */,
                 i3d::Vector3d<int> resolution /*  = {1, 1, 1} */,
                 const std::string version /* = "latest" */) {
	return ImageView(ip, port, uuid, channel, timepoint, angle, resolution,
	                 version)
	    .write_image(img);
}

/* ===================================== ImageView */

ImageView::ImageView(std::string ip,
                     int port,
                     std::string uuid,
                     int channel,
                     int timepoint,
                     int angle,
                     i3d::Vector3d<int> resolution,
                     std::string version)
    : _ip(std::move(ip)), _port(port), _uuid(std::move(uuid)),
      _channel(channel), _timepoint(timepoint), _angle(angle),
      _resolution(resolution), _version(std::move(version)) {}

template <cnpts::Scalar T>
i3d::Image3d<T> ImageView::read_block(i3d::Vector3d<int> coord) const {
	DatasetProperties props = get_dataset_properties(_ip, _port, _uuid);
	i3d::Vector3d<int> block_dim =
	    details::get_block_dimensions(props, _resolution);

	i3d::Image3d<T> img;
	i3d::Vector3d<int> block_size = details::data_manip::get_block_size(
	    coord, block_dim, props.dimensions / _resolution);

	img.MakeRoom(block_size);

	read_block(coord, img);
	return img;
}

template <cnpts::Scalar T>
bool ImageView::read_block(
    i3d::Vector3d<int> coord,
    i3d::Image3d<T>& dest,
    i3d::Vector3d<int> dest_offset /*  = {0, 0, 0} */) const {
	return read_blocks({coord}, dest, {dest_offset});
}

template <cnpts::Scalar T>
std::vector<i3d::Image3d<T>>
ImageView::read_blocks(const std::vector<i3d::Vector3d<int>>& coords) const {
	std::vector<i3d::Image3d<T>> out;
	for (auto coord : coords)
		out.push_back(read_block<T>(coord));

	return out;
}

// TODO optimise
template <cnpts::Scalar T>
bool ImageView::read_blocks(
    const std::vector<i3d::Vector3d<int>>& coords,
    i3d::Image3d<T>& dest,
    const std::vector<i3d::Vector3d<int>>& offsets) const {

	std::string dataset_url = details::get_dataset_url(_ip, _port, _uuid);
	DatasetProperties props = details::get_dataset_properties(dataset_url);
	i3d::Vector3d<int> block_dim =
	    details::get_block_dimensions(props, _resolution);

	i3d::Vector3d<int> img_dim = props.dimensions / _resolution;

	if (coords.size() != offsets.size()) {
		details::log::error("Count of coordinates != count of offsets");
		return false;
	}

	if (!details::check_block_coords(coords, img_dim, block_dim))
		return false;

	if (!details::check_offset_coords(offsets, coords, dest, block_dim,
	                                  img_dim))
		return false;

	std::string session_url = details::requests::session_url_request(
	    dataset_url, _resolution, _version);

	if (session_url.ends_with('/'))
		session_url.pop_back();

	for (std::size_t i = 0; i < coords.size(); ++i) {
		auto& coord = coords[i];
		auto& offset = offsets[i];

		std::string url =
		    fmt::format("{}/{}/{}/{}/{}/{}/{}", session_url, coord.x, coord.y,
		                coord.z, _timepoint, _channel, _angle);
		auto [data, response] = details::requests::make_request(url);

		details::data_manip::read_data(data, props.voxel_type, dest, offset);
	}
	return true;
}

template <cnpts::Scalar T>
i3d::Image3d<T> ImageView::read_image() const {
	DatasetProperties props = get_dataset_properties(_ip, _port, _uuid);
	i3d::Vector3d<int> block_dim =
	    details::get_block_dimensions(props, _resolution);
	i3d::Vector3d<int> img_dim = props.dimensions / _resolution;

	i3d::Vector3d<int> block_count =
	    (img_dim + block_dim - 1) / block_dim; // Ceiling

	i3d::Image3d<T> out;
	out.MakeRoom(img_dim);

	std::vector<i3d::Vector3d<int>> blocks;
	std::vector<i3d::Vector3d<int>> offsets;

	for (int x = 0; x < block_count.x; ++x)
		for (int y = 0; y < block_count.y; ++y)
			for (int z = 0; z < block_count.z; ++z) {
				blocks.emplace_back(x, y, z);
				offsets.emplace_back(x * block_dim.x, y * block_dim.y,
				                     z * block_dim.z);
			}

	read_blocks(blocks, out, offsets);
	return out;
}

template <cnpts::Scalar T>
bool ImageView::write_block(
    const i3d::Image3d<T>& src,
    i3d::Vector3d<int> coord,
    i3d::Vector3d<int> src_offset /*  = {0, 0, 0} */) const {
	return write_blocks(src, {coord}, {src_offset});
}

// TODO optimise
template <cnpts::Scalar T>
bool ImageView::write_blocks(
    const i3d::Image3d<T>& src,
    const std::vector<i3d::Vector3d<int>>& coords,
    const std::vector<i3d::Vector3d<int>>& src_offsets) const {

	std::string dataset_url = details::get_dataset_url(_ip, _port, _uuid);
	DatasetProperties props = details::get_dataset_properties(dataset_url);
	i3d::Vector3d<int> block_dim =
	    details::get_block_dimensions(props, _resolution);
	i3d::Vector3d<int> img_dim = props.dimensions / _resolution;

	if (coords.size() != src_offsets.size()) {
		details::log::error("Count of coordinates != count of offsets");
		return false;
	}

	if (!details::check_block_coords(coords, img_dim, block_dim))
		return false;

	if (!details::check_offset_coords(src_offsets, coords, src, block_dim,
	                                  img_dim))
		return false;

	std::string session_url = details::requests::session_url_request(
	    dataset_url, _resolution, _version);

	if (session_url.ends_with('/'))
		session_url.pop_back();

	for (std::size_t i = 0; i < coords.size(); ++i) {
		auto& coord = coords[i];
		auto& offset = src_offsets[i];

		i3d::Vector3d<int> block_size =
		    details::data_manip::get_block_size(coord, block_dim, img_dim);

		std::vector<char> data(details::data_manip::get_block_data_size(
		    block_size, props.voxel_type));

		details::data_manip::write_data(src, offset, data, props.voxel_type,
		                                block_size);

		std::string url =
		    fmt::format("{}/{}/{}/{}/{}/{}/{}", session_url, coord.x, coord.y,
		                coord.z, _timepoint, _channel, _angle);

		auto [_, response] = details::requests::make_request(
		    url, Poco::Net::HTTPRequest::HTTP_POST, data,
		    {{"Content-Type", "application/octet-stream"}});
	}

	return true;
}

template <cnpts::Scalar T>
bool ImageView::write_image(const i3d::Image3d<T>& img) const {
	DatasetProperties props = get_dataset_properties(_ip, _port, _uuid);
	i3d::Vector3d<int> block_dim =
	    details::get_block_dimensions(props, _resolution);
	i3d::Vector3d<int> img_dim = props.dimensions / _resolution;
	i3d::Vector3d<int> block_count =
	    (img_dim + block_dim - 1) / block_dim; // Ceiling

	std::vector<i3d::Vector3d<int>> blocks;
	std::vector<i3d::Vector3d<int>> offsets;

	for (int x = 0; x < block_count.x; ++x)
		for (int y = 0; y < block_count.y; ++y)
			for (int z = 0; z < block_count.z; ++z) {
				blocks.emplace_back(x, y, z);
				offsets.emplace_back(x * block_dim.x, y * block_dim.y,
				                     z * block_dim.z);
			}

	return write_blocks(img, blocks, offsets);
}

/* ===================================== Connection */

Connection::Connection(std::string ip, int port, std::string uuid)
    : _ip(std::move(ip)), _port(port), _uuid(std::move(uuid)) {}

ImageView Connection::get_view(int channel,
                               int timepoint,
                               int angle,
                               i3d::Vector3d<int> resolution,
                               const std::string& version) const {
	return ImageView(_ip, _port, _uuid, channel, timepoint, angle, resolution,
	                 version);
}

template <cnpts::Scalar T>
i3d::Image3d<T> Connection::read_block(i3d::Vector3d<int> coord,
                                       int channel,
                                       int timepoint,
                                       int angle,
                                       i3d::Vector3d<int> resolution,
                                       const std::string& version) const {
	return get_view(channel, timepoint, angle, resolution, version)
	    .read_block<T>(coord);
}

template <cnpts::Scalar T>
bool Connection::read_block(i3d::Vector3d<int> coord,
                            i3d::Image3d<T>& dest,
                            i3d::Vector3d<int> dest_offset,
                            int channel,
                            int timepoint,
                            int angle,
                            i3d::Vector3d<int> resolution,
                            const std::string& version) const {
	return get_view(channel, timepoint, angle, resolution, version)
	    .read_block(coord, dest, dest_offset);
}

template <cnpts::Scalar T>
std::vector<i3d::Image3d<T>>
Connection::read_blocks(const std::vector<i3d::Vector3d<int>>& coords,
                        int channel,
                        int timepoint,
                        int angle,
                        i3d::Vector3d<int> resolution,
                        const std::string& version) const {
	return get_view(channel, timepoint, angle, resolution, version)
	    .read_blocks<T>(coords);
}

template <cnpts::Scalar T>
bool Connection::read_blocks(
    const std::vector<i3d::Vector3d<int>>& coords,
    i3d::Image3d<T>& dest,
    const std::vector<i3d::Vector3d<int>>& dest_offsets,
    int channel,
    int timepoint,
    int angle,
    i3d::Vector3d<int> resolution,
    const std::string& version) const {
	return get_view(channel, timepoint, angle, resolution, version)
	    .read_blocks(coords, dest, dest_offsets);
}

template <cnpts::Scalar T>
i3d::Image3d<T> Connection::read_image(int channel,
                                       int timepoint,
                                       int angle,
                                       i3d::Vector3d<int> resolution,
                                       const std::string& version) const {
	return get_view(channel, timepoint, angle, resolution, version)
	    .read_image<T>();
}

template <cnpts::Scalar T>
bool Connection::write_block(const i3d::Image3d<T>& src,
                             i3d::Vector3d<int> coord,
                             i3d::Vector3d<int> src_offset,
                             int channel,
                             int timepoint,
                             int angle,
                             i3d::Vector3d<int> resolution,
                             const std::string& version) const {
	return get_view(channel, timepoint, angle, resolution, version)
	    .write_block(src, coord, src_offset);
}

template <cnpts::Scalar T>
bool Connection::write_blocks(
    const i3d::Image3d<T>& src,
    const std::vector<i3d::Vector3d<int>>& coords,
    const std::vector<i3d::Vector3d<int>>& src_offsets,
    int channel,
    int timepoint,
    int angle,
    i3d::Vector3d<int> resolution,
    const std::string& version) const {
	return get_view(channel, timepoint, angle, resolution, version)
	    .write_blocks(src, coords, src_offsets);
}

template <cnpts::Scalar T>
bool Connection::write_image(const i3d::Image3d<T>& src,
                             int channel,
                             int timepoint,
                             int angle,
                             i3d::Vector3d<int> resolution,
                             const std::string& version) const {
	return get_view(channel, timepoint, angle, resolution, version)
	    .write_image(src);
}

} // namespace datastore

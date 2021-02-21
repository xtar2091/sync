#include "FileWalker.h"

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <fmt/format.h>

#include "GlobalConf.h"

namespace
{
	std::string GetRelativeFileName(const std::string& history_file_name)
	{
		boost::filesystem::path path(GlobalConf::Instance()->local_conf.path);
		std::string root_path = (path / GlobalConf::Instance()->local_history_conf.path).string();
		int ind = root_path.size();
		if (history_file_name[ind] == '/' || history_file_name[ind] == '\\') {
			ind++;
		}
		return history_file_name.substr(ind);
	}

	std::string GetActuallyFileName(const std::string& file_name)
	{
		size_t last_dot_ind = file_name.find_last_of('.');
		if (last_dot_ind == std::string::npos) return "";
		size_t last_underline_ind = file_name.find_last_of('_');
		if (last_underline_ind == std::string::npos) return "";
		if (last_underline_ind >= last_dot_ind) return "";
		return file_name.substr(0, last_underline_ind) + file_name.substr(last_dot_ind);
	}

	std::string GetFileName(const std::string& history_file_name)
	{
		std::string file_name = GetRelativeFileName(history_file_name);
		file_name = GetActuallyFileName(file_name);
		return file_name;
	}
}

void FileWalker::WalkChangedFiles()
{
	boost::filesystem::path path(GlobalConf::Instance()->local_conf.path);
	std::string history_dir = (path / GlobalConf::Instance()->local_history_conf.path).string();
	boost::filesystem::recursive_directory_iterator end_it;
	boost::filesystem::recursive_directory_iterator it(history_dir);
	for (; it != end_it; it++) {
		if (!boost::filesystem::is_regular_file(it->path())) continue;
		std::string file_name = GetFileName(it->path().string());
		if (!file_name.empty()) {
			changed_files.insert(file_name);
		}
	}
}

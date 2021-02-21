#pragma once

#include <set>
#include <string>

class FileUploadManager
{
public:
	void UploadFiles(const std::set<std::string>& changed_files);

private:
	std::string GetLocalFileFullPath(const std::string& file_name);
	std::string GetRemoteFileFullPath(const std::string& file_name);
	void UploadFile(const std::string& local_file, const std::string& remote_file);
};


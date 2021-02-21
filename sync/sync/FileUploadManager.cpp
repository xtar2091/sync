#include "FileUploadManager.h"

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <fmt/format.h>
#include "GlobalConf.h"

void FileUploadManager::UploadFiles(const std::set<std::string>& changed_files)
{
    fmt::print("-----------------upload files begin-----------------\n");
    for (const std::string& changed_file_name : changed_files) {
        std::string local_file = GetLocalFileFullPath(changed_file_name);
        std::string remote_file = GetRemoteFileFullPath(changed_file_name);
        UploadFile(local_file, remote_file);
        fmt::print("{}\n", changed_file_name);
    }
    fmt::print("-----------------upload files end-----------------\n");
}

std::string FileUploadManager::GetLocalFileFullPath(const std::string& file_name)
{
    boost::filesystem::path path(GlobalConf::Instance()->local_conf.path);
    return (path / file_name).string();
}

std::string FileUploadManager::GetRemoteFileFullPath(const std::string& file_name)
{
    boost::filesystem::path path(GlobalConf::Instance()->remote_conf.path);
    std::string remote_file = (path / file_name).string();
    boost::replace_all(remote_file, "\\", "/");
    return remote_file;
}

void FileUploadManager::UploadFile(const std::string& local_file, const std::string& remote_file)
{
    std::string cmd = fmt::format("{} {} {}",
        GlobalConf::Instance()->upload_conf.command, local_file, remote_file);
#ifdef PLATFORM_WINDWS
    cmd = "bash " + cmd;
#endif // PLATFORM_WINDWS
    int ret = system(cmd.c_str());
    if (ret != 0)
    {
        throw std::runtime_error(fmt::format("upload file failed, local file: {}, remote file: {}",
            local_file, remote_file));
    }
}

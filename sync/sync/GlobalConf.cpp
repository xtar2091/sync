#include "GlobalConf.h"

#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>

namespace
{
    void ParseFileToJson(const std::string& file_name, nlohmann::json& json)
    {
        try
        {
            std::ifstream ifs(file_name);
            ifs >> json;
        }
        catch (const std::exception&)
        {
            throw std::runtime_error(fmt::format("parse conf file failed: {}", file_name));
        }
    }

    void ParseLocalConf(const std::string& file_name, const nlohmann::json& conf_json, GlobalConf::LocalConf& conf)
    {
        if ((conf_json.find("local") == conf_json.end()) || !conf_json["local"].is_object()) {
            throw std::runtime_error(fmt::format("invalid conf file: {}, field missed or invalid type: $.local", file_name));
        }
        const nlohmann::json& local_conf_json = conf_json["local"];

        if ((local_conf_json.find("path") == local_conf_json.end()) || !local_conf_json["path"].is_string()) {
            throw std::runtime_error(fmt::format("invalid conf file: {}, field missed or invalid type: $.local.path", file_name));
        }
        conf.path = local_conf_json["path"].get<std::string>();
        boost::trim(conf.path);
        if (conf.path.empty()) {
            throw std::runtime_error(fmt::format("invalid conf file: {}, value is empty: $.local.path", file_name));
        }
    }

    void ParseRemoteConf(const std::string& file_name, const nlohmann::json& conf_json, GlobalConf::RemoteConf& conf)
    {
        if ((conf_json.find("remote") == conf_json.end()) || !conf_json["remote"].is_object()) {
            throw std::runtime_error(fmt::format("invalid conf file: {}, field missed or invalid type: $.remote", file_name));
        }
        const nlohmann::json& remote_conf_json = conf_json["remote"];

        if ((remote_conf_json.find("path") == remote_conf_json.end()) || !remote_conf_json["path"].is_string()) {
            throw std::runtime_error(fmt::format("invalid conf file: {}, field missed or invalid type: $.remote.path", file_name));
        }
        conf.path = remote_conf_json["path"].get<std::string>();
        boost::trim(conf.path);
        if (conf.path.empty()) {
            throw std::runtime_error(fmt::format("invalid conf file: {}, value is empty: $.remote.path", file_name));
        }
    }

    void ParseUploadConf(const std::string& file_name, const nlohmann::json& conf_json, GlobalConf::UploadConf& conf)
    {
        if ((conf_json.find("upload") == conf_json.end()) || !conf_json["upload"].is_object()) {
            throw std::runtime_error(fmt::format("invalid conf file: {}, field missed or invalid type: $.upload", file_name));
        }
        const nlohmann::json& upload_conf_json = conf_json["upload"];

        if ((upload_conf_json.find("command") == upload_conf_json.end()) || !upload_conf_json["command"].is_string()) {
            throw std::runtime_error(fmt::format("invalid conf file: {}, field missed or invalid type: $.upload.command", file_name));
        }
        conf.command = upload_conf_json["command"].get<std::string>();
        boost::trim(conf.command);
        if (conf.command.empty()) {
            throw std::runtime_error(fmt::format("invalid conf file: {}, value is empty: $.upload.command", file_name));
        }
    }

    void ParseLocalHistoryConf(const std::string& file_name, const nlohmann::json& conf_json, GlobalConf::LocalHistoryConf& conf)
    {
        if ((conf_json.find("history") == conf_json.end()) || !conf_json["history"].is_object()) {
            throw std::runtime_error(fmt::format("invalid conf file: {}, field missed or invalid type: $.history", file_name));
        }
        const nlohmann::json& history_conf_json = conf_json["history"];

        if ((history_conf_json.find("path") == history_conf_json.end()) || !history_conf_json["path"].is_string()) {
            throw std::runtime_error(fmt::format("invalid conf file: {}, field missed or invalid type: $.history.path", file_name));
        }
        conf.path = history_conf_json["path"].get<std::string>();
        boost::trim(conf.path);
        if (conf.path.empty()) {
            throw std::runtime_error(fmt::format("invalid conf file: {}, value is empty: $.history.path", file_name));
        }
    }
}

GlobalConf* GlobalConf::Instance()
{
    static GlobalConf inst;
    return &inst;
}

void GlobalConf::Init(const std::string& conf_root_path)
{
    SetConfFilesFullPath(conf_root_path);
    CheckConfFiles();

    nlohmann::json conf;
    ParseFileToJson(conf_json_path, conf);
    ParseLocalConf(conf_json_path, conf, local_conf);
    ParseRemoteConf(conf_json_path, conf, remote_conf);
    ParseUploadConf(conf_json_path, conf, upload_conf);
    ParseLocalHistoryConf(conf_json_path, conf, local_history_conf);

    CheckConf();
}

void GlobalConf::SetConfFilesFullPath(const std::string& conf_root_path)
{
    boost::filesystem::path path(conf_root_path);
    conf_json_path = (path / "conf.json").string();
}

void GlobalConf::CheckConfFiles()
{
    if (!boost::filesystem::is_regular_file(conf_json_path)) {
        throw std::runtime_error(fmt::format("file not found: {}", conf_json_path));
    }
}

void GlobalConf::CheckConf()
{
    if (!boost::filesystem::is_directory(local_conf.path)) {
        throw std::runtime_error(fmt::format("local path not found: {}", local_conf.path));
    }
    boost::filesystem::path path(local_conf.path);
    if (!boost::filesystem::is_directory(path / local_history_conf.path)) {
        throw std::runtime_error(fmt::format("local history path not found: {}", local_history_conf.path));
    }
}

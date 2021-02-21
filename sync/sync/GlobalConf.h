#pragma once

#include <string>

class GlobalConf
{
public:
	struct LocalHistoryConf
	{
		std::string path;
	};

	struct LocalConf
	{
		std::string path;
	};

	struct RemoteConf
	{
		std::string path;
	};

	struct UploadConf
	{
		std::string command;
	};

public:
	static GlobalConf* Instance();
	void Init(const std::string& conf_root_path);

public:
	LocalConf local_conf;
	RemoteConf remote_conf;
	LocalHistoryConf local_history_conf;
	UploadConf upload_conf;
	std::string conf_json_path;///< .sync/conf.json完整路径名

private:
	GlobalConf() = default;
	GlobalConf(GlobalConf&&) = default;
	GlobalConf(const GlobalConf&) = default;
	GlobalConf& operator=(GlobalConf&&) = default;
	GlobalConf& operator=(const GlobalConf&) = default;

private:
	void SetConfFilesFullPath(const std::string& conf_root_path);
	void CheckConfFiles();
	void CheckConf();
};


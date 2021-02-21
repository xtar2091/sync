#include "FileCleanManager.h"

#include <boost/filesystem.hpp>
#include "GlobalConf.h"

void FileCleanManager::Clean()
{
	boost::filesystem::path path(GlobalConf::Instance()->local_conf.path);
	path /= GlobalConf::Instance()->local_history_conf.path;
	for (boost::filesystem::directory_iterator it(path); it != boost::filesystem::directory_iterator(); it++)
	{
		boost::filesystem::remove_all(it->path());
	}
}

#include <iostream>

#include <fmt/format.h>

#include "CommanLine.h"
#include "FileCleanManager.h"
#include "FileUploadManager.h"
#include "FileWalker.h"
#include "GlobalConf.h"

int main(int argc, char* argv[]) {
	int ret = 1;
	do
	{
		try
		{
			if (!CommanLine::Check(argc, argv)) break;
			GlobalConf::Instance()->Init(argv[1]);
			FileWalker fw;
			fw.WalkChangedFiles();
			FileUploadManager upload_mgr;
			upload_mgr.UploadFiles(fw.changed_files);
			FileCleanManager clean_mgr;
			clean_mgr.Clean();
			ret = 0;
		}
		catch (const std::exception& err) {
			fmt::print("{}\n", err.what());
		}
	} while (false);
	return ret;
}

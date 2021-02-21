#pragma once

#include <string>
#include <set>

class FileWalker
{
public:
	void WalkChangedFiles();

public:
	std::set<std::string> changed_files;
};


#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <list>
#include <memory>
#include <string>
#include <algorithm>

#include "FileSystemObject.h"
#include "FileSystemObjectsContainer.h"

class Directory : public FileSystemObject, public FileSystemObjectsContainer {
	std::vector<std::shared_ptr<FileSystemObject> > nestedObjects;
public:
	Directory(std::string name) : FileSystemObject(name) {}

	size_t getSize() const override {
		size_t size = 0;
		for (auto objPtr : this->nestedObjects) {
			size += objPtr->getSize();
		}

		return size;
	}

	std::vector<std::shared_ptr<FileSystemObject> >::const_iterator begin() const override {
		return this->nestedObjects.begin();
	}

	std::vector<std::shared_ptr<FileSystemObject> >::const_iterator end() const override {
		return this->nestedObjects.end();
	}

	void remove(std::shared_ptr<FileSystemObject> obj) override {
		this->nestedObjects.erase(std::find(this->nestedObjects.begin(), this->nestedObjects.end(), obj));
	}

	void add(const std::shared_ptr<FileSystemObject>& obj) override {
		this->nestedObjects.push_back(obj);
	}
};

#endif // !DIRECTORY_H


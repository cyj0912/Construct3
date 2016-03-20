//This is the serialization toolbox

#pragma once

#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

namespace mf {

inline std::string to_string(const glm::vec2& vec2)
{
	return std::to_string(vec2.x) + " " + std::to_string(vec2.y);
}

inline glm::vec2 stovec2(const std::string& str)
{
	std::stringstream ss;
	ss << str;
	std::string a;
	glm::vec2 ret;
	ss >> a;
	ret.x = std::stof(a);
	ss >> a;
	ret.y = std::stof(a);
	return ret;
}

class ObjectReader
{
public:
	rapidjson::Document* Document;
	rapidjson::Value* Object;

	ObjectReader(rapidjson::Document* doc, rapidjson::Value* node)
	{
		Document = doc;
		Object = node;
	}

	std::string GetClass()
	{
		return (*Object)["@CLASS"].GetString();
	}

	std::string GetProperty(const std::string& name)
	{
		return (*Object)[name.c_str()].GetString();
	}

	ObjectReader GetArray(const std::string& name)
	{
		rapidjson::Value* val = &(*Object)[name.c_str()];
		return ObjectReader(Document, val);
	}

	std::vector<ObjectReader> GetArrayElements()
	{
		std::vector<ObjectReader> result;
		for (rapidjson::Value::ValueIterator iter = Object->Begin(); iter != Object->End(); ++iter)
		{
			result.push_back(ObjectReader(Document, &(*iter)));
		}
		return result;
	}
};

class ObjectWrtier
{
public:
	rapidjson::Document* Document;
	rapidjson::Value* Object;

	ObjectWrtier(rapidjson::Document* doc, rapidjson::Value* node)
	{
		Document = doc;
		Object = node;
	}

	void SetClass(const std::string& name)
	{
		rapidjson::Value n;
		n.SetString(name.c_str(), name.length(), Document->GetAllocator());
		Object->AddMember("@CLASS", n, Document->GetAllocator());
	}

	void SetProperty(const std::string& name, const std::string& value)
	{
		rapidjson::Value n;
		n.SetString(name.c_str(), name.length(), Document->GetAllocator());
		rapidjson::Value val;
		val.SetString(value.c_str(), value.length(), Document->GetAllocator());
		Object->AddMember(n, val, Document->GetAllocator());
	}

	ObjectWrtier AddArray(const std::string& name)
	{
		rapidjson::Value n;
		n.SetString(name.c_str(), name.length(), Document->GetAllocator());
		rapidjson::Value v;
		v.SetArray();
		&Object->AddMember(n, v, Document->GetAllocator());
		rapidjson::Value* retv = &(*Object)[name.c_str()];
		return ObjectWrtier(Document, retv);
	}

	ObjectWrtier AddArrayElementObject()
	{
		rapidjson::Value v;
		v.SetObject();
		Object->PushBack(v, Document->GetAllocator());
		rapidjson::Value* retv = &(*Object)[Object->Size() - 1];
		return ObjectWrtier(Document, retv);
	}
};

class SerializedFile
{
public:
	SerializedFile(const std::string& name)
	{
		FileName = name;
		Document.SetObject();
	}

	ObjectReader GetReader()
	{
		return ObjectReader(&Document, &Document);
	}

	ObjectWrtier GetWriter()
	{
		return ObjectWrtier(&Document, &Document);
	}

	std::string GetJson()
	{
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		Document.Accept(writer);
		return buffer.GetString();
	}

	void Save()
	{
		std::fstream file(FileName, std::ios::out);
		file << GetJson();
		file.close();
	}

	void Load()
	{
		FILE* f = std::fopen(FileName.c_str(), "rb");
		char readBuffer[65536];
		rapidjson::FileReadStream is(f, readBuffer, sizeof(readBuffer));
		Document.ParseStream(is);
		std::fclose(f);
	}

	std::string FileName;
	rapidjson::Document Document;
};

class Serializable
{
public:
	virtual void Serialize(ObjectWrtier& obj)
	{
		//Never reached
	}

	virtual void Deserialize(ObjectReader& obj)
	{
		//Never reached
	}
};

}

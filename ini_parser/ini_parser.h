#ifndef QIHOO_INI_PARSER_H_
#define QIHOO_INI_PARSER_H_

#include <string>
#include <unordered_map>
#include <memory>
namespace qh
{
	class INIParser
	{
	public:
		INIParser() 
		{
			empty = "";
		}
		~INIParser() {}

		//! \brief 解析一个磁盘上的INI文件
		//! \param[in] - const std::string & ini_file_path
		//! \return - bool
		//bool Parse(const std::string& ini_file_path);

		//! \brief 解析一段形如INI格式的内存数据。
		//!   例如：ini_data="a:1||b:2||c:3"
		//!         调用<code>Parse(ini_data, ini_data_len, "||", ":")</code>即可解析出这段数据。
		//!         解析完毕之后 
		//!         Get("a")=="1" && Get("b")=="2" && Get("c")=="3"
		//! \param[in] - const char * ini_data
		//! \param[in] - size_t ini_data
		//! \param[in] - const std::string & line_seperator
		//! \param[in] - const std::string & key_value_seperator
		//! \return - bool
		bool Parse(const char* ini_data, size_t ini_data_len, const std::string& line_seperator = "\n", const std::string& key_value_seperator = "=");

		//! \brief 从默认section中查找某个key，并返回找到的value。如果找不到，返回一个空串
		//! \param[in] - const std::string & key
		//! \param[in] - bool * found - 输出参数，true表明找到这个key
		//! \return - const std::string& - 返回的具体key对应的value
		const std::string& Get(const std::string& key, bool* found);

		//const std::string& Get(const std::string& section, const std::string& key, bool* found);
		const std::string& INIParser::Get(const std::string& key);

	private:
		std::string empty;
		std::unordered_map<std::string, std::string> mkey_value;
	};
	bool INIParser::Parse(const char* ini_data, size_t ini_data_len, const std::string& line_seperator , const std::string& key_value_seperator )
	{
		if (ini_data == NULL || ini_data_len == 0 || line_seperator.size() == 0 || key_value_seperator.size() == 0)
			return false;
		 std::string  s = ini_data;
		 size_t pos = 0;
		 while (pos != std::string::npos) {
				pos = s.find_first_not_of(line_seperator, pos);
				if (pos == std::string::npos)break;
			    auto pos_ = s.find_first_of(key_value_seperator, pos);
				std::string key;
				 key.assign(s.begin() + pos, s.begin() + pos_);

				 pos = s.find_first_of(line_seperator, pos);
				 std::string value;
				 if (pos == std::string::npos){
					 value.assign(s.begin() + pos_ + 1, s.end());
				 }else
				    value.assign(s.begin() + pos_ + 1, s.begin() + pos);
				 mkey_value.insert(std::make_pair(key, value));
		 }
		 return true;
	}
	const std::string& INIParser::Get(const std::string& key, bool* found)
	{
		//std::string value="";
		auto result = mkey_value.find(key);
		if (result != mkey_value.end())return mkey_value[key];
		//*found = true;
		return this->empty;
	}
	const std::string& INIParser::Get(const std::string& key)
	{
		auto result = mkey_value.find(key);
		if (result == mkey_value.end())return NULL;
		//*found = true;
		return mkey_value[key];
	}
}

#endif


#pragma once
#include "ofMain.h"
#include "ofxTrueTypeFontUL2.h"
#include "ofxJSON.h"
#include "SHEEPresentationAssets.h"

#define SHP_FONT_DEFAULT_SCALE 36

namespace SHEEPre
{
	enum layoutData {
		LAYOUT_HORIZONTAL,
		LAYOUT_VERTICAL,
		LAYOUT_CENTER
	};

	enum contentType {
		CTYPE_TEXT,
		CTYPE_IMAGE,
		CTYPE_VIDEO,
		CTYPE_SOUND,
		CTYPE_MODEL
	};

	enum contentStyle {
		STYLE_THEME,
		STYLE_DETAIL,
		STYLE_EXTRA
	};

	class content {
	public:
		string value = "Value";
		contentType type = CTYPE_TEXT;
		contentStyle style = STYLE_THEME;
		ofRectangle viewArea;

		int alignType = UL2_TEXT_ALIGN_CENTER | UL2_TEXT_ALIGN_V_MIDDLE;
		int textScale = SHP_FONT_DEFAULT_SCALE;
		ofPtr<ofImage> asset_image;
	};

	class block {
	public:
		vector< ofPtr<content> > contents;
	};

	class page {
	public:
		vector< ofPtr<block> > blocks;
		layoutData layout = LAYOUT_HORIZONTAL;
	};

	class Theme {
	public:
		Theme(string t) { title = t; }
		~Theme() {}
		string title = "New Theme";
		vector< ofPtr<page> > pages;
	};
}

class SHEEPresentationData
{
public:
	SHEEPresentationData();
	~SHEEPresentationData();

	SHEEPresentationAssets assets;

	ofPtr<SHEEPre::Theme> addTheme(string title);
	ofPtr<SHEEPre::page> addPage(string theme);
	ofPtr<SHEEPre::page> addPage(int themeIndex);
	ofPtr<SHEEPre::block> addBlock(int theme, int page);
	ofPtr<SHEEPre::content> addContent(int th, int pg, int bl);

	ofPtr<SHEEPre::Theme> getTheme(int th);
	ofPtr<SHEEPre::page> getPage(int th, int pg);
	ofPtr<SHEEPre::block> getBlock(int th, int pg, int bl);
	ofPtr<SHEEPre::content> getContent(int th, int pg, int bl, int ct);

	/*======DATA======*/
	int width = 1920;
	int height = 1080;

	vector< ofPtr<SHEEPre::Theme> > themes;

	void saveToJSON(string path);
	void loadFromJSON(string path);

	string utf8_to_shiftJIS(string s)
	{
		wstring ws = utf8_to_wide_winapi(s);
		return wide_to_multi_winapi(ws);
	}

	std::wstring utf8_to_wide_winapi(std::string const& src)
	{
		auto const dest_size = ::MultiByteToWideChar(CP_UTF8, 0U, src.data(), -1, nullptr, 0U);
		std::vector<wchar_t> dest(dest_size, L'\0');
		if (::MultiByteToWideChar(CP_UTF8, 0U, src.data(), -1, dest.data(), dest.size()) == 0) {
			throw std::system_error{ static_cast<int>(::GetLastError()), std::system_category() };
		}
		dest.resize(std::char_traits<wchar_t>::length(dest.data()));
		dest.shrink_to_fit();
		return std::wstring(dest.begin(), dest.end());
	}

	std::string wide_to_multi_winapi(std::wstring const& src)
	{
		auto const dest_size = ::WideCharToMultiByte(CP_ACP, 0U, src.data(), -1, nullptr, 0, nullptr, nullptr);
		std::vector<char> dest(dest_size, '\0');
		if (::WideCharToMultiByte(CP_ACP, 0U, src.data(), -1, dest.data(), dest.size(), nullptr, nullptr) == 0) {
			throw std::system_error{ static_cast<int>(::GetLastError()), std::system_category() };
		}
		dest.resize(std::char_traits<char>::length(dest.data()));
		dest.shrink_to_fit();
		return std::string(dest.begin(), dest.end());
	}
};


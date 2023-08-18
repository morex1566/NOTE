#pragma once

inline std::wstring StringToWString(const std::string& narrowString) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(narrowString);
}
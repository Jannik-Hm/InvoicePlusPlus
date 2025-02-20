#ifndef PDF_UTILS_H
#define PDF_UTILS_H

#include <hpdf.h>
#include <iostream>
#include <string>
#include "../utils.h"

inline void
  error_handler (HPDF_STATUS   error_no,
                 HPDF_STATUS   detail_no,
                 void         *user_data)
{
    /* throw exception when an error has occured */
    printf ("ERROR: error_no=%04X, detail_no=%d\n", (unsigned int)error_no,
        (int)detail_no);
    throw std::exception ();
}

inline HPDF_REAL calculate_text_height(const HPDF_Page page, const char *text, HPDF_REAL max_width,
                                       HPDF_REAL line_height, HPDF_REAL max_lines = NULL) {
    HPDF_REAL real_width;
    const char *current_text = text;
    size_t total_lines = 0;

    while (*current_text != '\0') {
        HPDF_UINT len = HPDF_Page_MeasureText(page, current_text, max_width, HPDF_TRUE, &real_width);
        if (len == 0) {
            break;
        }
        total_lines++;
        current_text += len;
        if (max_lines != NULL and total_lines == max_lines) {
            break;
        }
    }

    return total_lines * line_height;
}

inline HPDF_REAL writeText(const HPDF_Page page, std::string text, HPDF_REAL left,
                    HPDF_REAL top, HPDF_REAL line_height, HPDF_REAL max_width, _HPDF_TextAlignment alignment, HPDF_REAL max_height) {

    HPDF_REAL font_size = HPDF_Page_GetCurrentFontSize(page);

    HPDF_REAL bottom = (max_height == NULL) ? NULL : (top - max_height);

    text = UTF8toISO8859_1(text);

    HPDF_REAL textHeight = calculate_text_height(page, text.c_str(), max_width, font_size, max_height);

    HPDF_Page_BeginText(page);
    HPDF_Page_TextRect(page, left, top, left + max_width, bottom, text.c_str(), alignment,
                       nullptr);
    HPDF_Page_EndText(page);
    return textHeight;
}

inline HPDF_REAL writeTextIfNotHeightExceeded(const HPDF_Page page, std::string text, HPDF_REAL left,
                    HPDF_REAL top, HPDF_REAL line_height, HPDF_REAL max_width, _HPDF_TextAlignment alignment, HPDF_REAL max_height) {

    HPDF_REAL font_size = HPDF_Page_GetCurrentFontSize(page);

    HPDF_REAL bottom = (max_height == NULL) ? NULL : (top - max_height);

    text = UTF8toISO8859_1(text);

    HPDF_REAL textHeight = calculate_text_height(page, text.c_str(), max_width, font_size, NULL);

    if (textHeight > max_height) {
        return 0;
    }

    HPDF_Page_BeginText(page);
    HPDF_Page_TextRect(page, left, top, left + max_width, bottom, text.c_str(), alignment,
                       nullptr);
    HPDF_Page_EndText(page);
    return textHeight;
}

inline HPDF_REAL writeText(const HPDF_Page page, std::string text, HPDF_REAL left,
                    HPDF_REAL top, HPDF_REAL line_height, HPDF_REAL max_width, _HPDF_TextAlignment alignment, int max_lines = 0) {

    HPDF_REAL font_size = HPDF_Page_GetCurrentFontSize(page);

    HPDF_REAL bottom = (max_lines == NULL) ? NULL : (top - max_lines * line_height);

    text = UTF8toISO8859_1(text);

    HPDF_REAL textHeight = calculate_text_height(page, text.c_str(), max_width, font_size, max_lines);

    HPDF_Page_BeginText(page);
    HPDF_Page_TextRect(page, left, top, left + max_width, bottom, text.c_str(), alignment,
                       nullptr);
    HPDF_Page_EndText(page);
    return textHeight;
}

inline HPDF_REAL writeTextIfNotLinesExceeded(const HPDF_Page page, std::string text, HPDF_REAL left,
                    HPDF_REAL top, HPDF_REAL line_height, HPDF_REAL max_width, _HPDF_TextAlignment alignment, int max_lines = 0) {

    HPDF_REAL font_size = HPDF_Page_GetCurrentFontSize(page);

    HPDF_REAL bottom = (max_lines == NULL) ? NULL : (top - max_lines * line_height);

    text = UTF8toISO8859_1(text);

    HPDF_REAL textHeight = calculate_text_height(page, text.c_str(), max_width, font_size, NULL);
    std::cout << textHeight << " " << max_lines * line_height << std::endl;
    if (textHeight > max_lines * line_height) {
        return 0;
    }
    HPDF_Page_BeginText(page);
    HPDF_Page_TextRect(page, left, top, left + max_width, bottom, text.c_str(), alignment,
                       nullptr);
    HPDF_Page_EndText(page);
    return textHeight;
}

inline HPDF_REAL changeFont(const HPDF_Page page, HPDF_REAL font_size, HPDF_Font font) {
    float line_height = font_size * 1.2;
    HPDF_Page_SetFontAndSize(page, font, font_size);
    HPDF_Page_SetTextLeading(page, line_height);
    return line_height;
}

#endif //PDF_UTILS_H

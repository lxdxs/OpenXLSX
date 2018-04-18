/*

   ____                               ____      ___ ____       ____  ____      ___
  6MMMMb                              `MM(      )M' `MM'      6MMMMb\`MM(      )M'
 8P    Y8                              `MM.     d'   MM      6M'    ` `MM.     d'
6M      Mb __ ____     ____  ___  __    `MM.   d'    MM      MM        `MM.   d'
MM      MM `M6MMMMb   6MMMMb `MM 6MMb    `MM. d'     MM      YM.        `MM. d'
MM      MM  MM'  `Mb 6M'  `Mb MMM9 `Mb    `MMd       MM       YMMMMb     `MMd
MM      MM  MM    MM MM    MM MM'   MM     dMM.      MM           `Mb     dMM.
MM      MM  MM    MM MMMMMMMM MM    MM    d'`MM.     MM            MM    d'`MM.
YM      M9  MM    MM MM       MM    MM   d'  `MM.    MM            MM   d'  `MM.
 8b    d8   MM.  ,M9 YM    d9 MM    MM  d'    `MM.   MM    / L    ,M9  d'    `MM.
  YMMMM9    MMYMMM9   YMMMM9 _MM_  _MM_M(_    _)MM_ _MMMMMMM MYMMMM9 _M(_    _)MM_
            MM
            MM
           _MM_

  Copyright (c) 2018, Kenneth Troldal Balslev

  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  - Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  - Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
  - Neither the name of the author nor the
    names of any contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */

#ifndef OPENXL_XLWORKBOOK_H
#define OPENXL_XLWORKBOOK_H

#include "XLAbstractXMLFile.h"
#include "XLRelationships.h"
#include "XLSharedStrings.h"
#include "XLSpreadsheetElement.h"

namespace OpenXLSX
{
    class XLSharedStrings;
    class XLAbstractSheet;
    class XLWorksheet;
    class XLChartsheet;
    class XLStyles;

//======================================================================================================================
//========== XLSheetMap Alias ==========================================================================================
//======================================================================================================================

    /**
     * @brief
     */
    using XLSheetMap = std::map<std::string, std::unique_ptr<XLAbstractSheet>>;

//======================================================================================================================
//========== XLWorkbook Class ==========================================================================================
//======================================================================================================================

/**
 * @brief This class encapsulates the concept of a Workbook. It provides access to the embedded sheets
 * (worksheets or chartsheets), as well as functionality for adding, deleting and renaming sheets.
 */
    class XLWorkbook: public XLAbstractXMLFile,
                      public XLSpreadsheetElement
    {
        friend class XLAbstractSheet;

//----------------------------------------------------------------------------------------------------------------------
//           Public Member Functions
//----------------------------------------------------------------------------------------------------------------------

    public:

        /**
         * @brief Constructor. Takes a reference to the parent XLDocument and a std::string with the relative path as
         * arguments.
         * @param parent A reference to the parent XLDocument object.
         * @param filePath The relative path to the underlying XML file.
         * @note Do not create an XLWorkbook object directly. Get access through the an XLDocument object.
         */
        explicit XLWorkbook(XLDocument &parent, const std::string &filePath);

        /**
         * @brief Copy Constructor.
         * @param other The XLWorkbook object to be copied.
         * @note The copy constructor has been explicitly deleted, as XLWorkbook objects should not be copied.
         */
        XLWorkbook(const XLWorkbook &other) = delete;

        /**
         * @brief Copy assignment operator.
         * @param other The XLWorkbook object to be assigned to the current.
         * @return A reference to *this
         * @note The copy assignment operator has been explicitly deleted, as XLWorkbook objects should not be copied.
         */
        XLWorkbook &operator=(const XLWorkbook &other) = delete;

        /**
         * @brief Move constructor.
         * @param other The XLWorkbook to be moved.
         * @note The move constructor has been explicitly deleted, as XLWorkbook objects should not be moved.
         */
        XLWorkbook(XLWorkbook &&other) = delete;

        /**
         * @brief Move assignment operator.
         * @param other The XLWorkbook to be move assigned.
         * @return A reference to *this
         * @note The move assignment operator has been explicitly deleted, as XLWorkbook objects should not be moved.
         */
        XLWorkbook &operator=(XLWorkbook &&other) = delete;

        /**
         * @brief Destructor
         * @note Default destructor specified
         */
        ~XLWorkbook() override = default;

        /**
         * @brief Get the sheet (worksheet or chartsheet) at the given index.
         * @param index The index et which the desired sheet is located.
         * @return A pointer to an XLAbstractSheet with the sheet at the index.
         * @todo This method is currently unimplemented.
         * @todo What should happen if the index is invalid?
         */
        XLAbstractSheet *Sheet(unsigned int index);

        /**
         * @brief Get the sheet (worksheet or chartsheet) with the given name.
         * @param sheetName The name at which the desired sheet is located.
         * @return A pointer to an XLAbstractSheet with the sheet at the index.
         * @todo This method is currently unimplemented.
         * @todo What should happen if the name is invalid?
         */
        XLAbstractSheet *Sheet(const std::string &sheetName);

        /**
         * @brief
         * @param sheetName
         * @return
         */
        XLWorksheet *Worksheet(const std::string &sheetName);

        /**
         * @brief
         * @param sheetName
         * @return
         */
        const XLWorksheet *Worksheet(const std::string &sheetName) const;

        /**
         * @brief
         * @param sheetName
         * @return
         */
        XLChartsheet *Chartsheet(const std::string &sheetName);

        /**
         * @brief
         * @param sheetName
         * @return
         */
        const XLChartsheet *Chartsheet(const std::string &sheetName) const;

        /**
         * @brief
         * @param sheetName
         */
        void DeleteSheet(const std::string &sheetName);

        /**
         * @brief Add a new worksheet to the workbook, with the given name and index.
         * @param sheetName The name of the worksheet.
         * @param index The index at which the worksheet should be inserted.
         */
        void AddWorksheet(const std::string &sheetName, unsigned int index = 0);

        /**
         * @brief Clone an existing worksheet.
         * @param extName The name of the worksheet to clone.
         * @param newName The name of the cloned worksheet.
         * @param index The index at which the worksheet should be inserted.
         * @todo The function works, but Excel reports errors when opening.
         * @todo Is it possible to have a common CloneSheet function?
         */
        void CloneWorksheet(const std::string &extName,
                            const std::string &newName,
                            unsigned int index = 0);

        /**
         * @brief Add a new chartsheet to the workbook, with the given name and index.
         * @param sheetName The name of the chartsheet.
         * @param index The index at which the chartsheet should be inserted.
         * @todo This method is currently unimplemented.
         */
        void AddChartsheet(const std::string &sheetName, unsigned int index = 0);

        /**
         * @brief
         * @param index
         */
        void MoveSheet(unsigned int index);

        /**
         * @brief
         * @param sheetName
         * @return
         */
        unsigned int IndexOfSheet(const std::string &sheetName);

        /**
         * @brief
         * @param sheetName
         * @param index
         */
        void SetIndexOfSheet(const std::string &sheetName, unsigned int index);

        /**
         * @brief
         * @return
         */
        unsigned int SheetCount() const;

        /**
         * @brief
         * @return
         */
        unsigned int WorksheetCount() const;

        /**
         * @brief
         * @return
         */
        unsigned int ChartsheetCount() const;

        /**
         * @brief
         * @param sheetName
         * @return
         */
        bool SheetExists(const std::string &sheetName) const;

        /**
         * @brief
         * @param sheetName
         * @return
         */
        bool WorksheetExists(const std::string &sheetName) const;

        /**
         * @brief
         * @param sheetName
         * @return
         */
        bool ChartsheetExists(const std::string &sheetName) const;

        /**
         * @brief
         * @return
         */
        XLSharedStrings *SharedStrings() const;

        /**
         * @brief
         * @return
         */
        bool HasSharedStrings() const;

        /**
         * @brief
         */
        void DeleteNamedRanges();

        /**
         * @brief
         */
        XLStyles *Styles();


//----------------------------------------------------------------------------------------------------------------------
//           Protected Member Functions
//----------------------------------------------------------------------------------------------------------------------

    protected:

        /**
         * @brief
         * @return
         */
        bool ParseXMLData() override;

        /**
         * @brief
         * @return
         */
        XLRelationships *Relationships();

        /**
         * @brief
         * @return
         */
        const XLRelationships *Relationships() const;

        /**
         * @brief
         * @param sheetName
         * @return
         */
        XMLNode *SheetNode(const std::string &sheetName);

//----------------------------------------------------------------------------------------------------------------------
//           Private Member Functions
//----------------------------------------------------------------------------------------------------------------------

    private:

        /**
         * @brief
         * @param item
         */
        void CreateSharedStrings(const XLRelationshipItem &item);

        /**
         * @brief
         * @param item
         */
        void CreateStyles(const XLRelationshipItem &item);

        /**
         * @brief
         * @param item
         */
        void CreateWorksheet(const XLRelationshipItem &item, const std::string&xmlData = "");

        /**
         * @brief
         * @param item
         */
        void CreateChartsheet(const XLRelationshipItem &item);

        /**
         * @brief Helper function to create a new XML file to hold the data for a new worksheet.
         * @param sheetName The name of the new worksheet.
         * @param index The index at which to insert the new worksheet.
         * @param xmlData The XML content of the file
         * @return A reference to the XLRelationshipItem corresponding to the worksheet file
         * @todo Provide a default content for the file.
         * @todo Consider having this as a static function in the XLWorksheet class.
         */
        XLRelationshipItem *InitiateWorksheet(const std::string &sheetName,
                                              unsigned int index,
                                              const std::string &xmlData);


//----------------------------------------------------------------------------------------------------------------------
//           Private Member Variables
//----------------------------------------------------------------------------------------------------------------------

    private:

        XMLNode *m_sheetsNode; /**< The parent node for all the sheet nodes (worksheets as well as chartsheets). */

        std::map<std::string, XMLNode *> m_sheetNodes; /**< Data structure for alle the sheetnodes in workbook.xml  */
        mutable XLSheetMap m_sheets; /**< Data structure for all sheets. */
        std::map<std::string, std::string> m_sheetPaths; /**<  */

        int m_sheetId; /**< Counter to use to create ID for new sheet */

        unsigned int m_sheetCount; /**< Holds the total sheet count. */
        unsigned int m_worksheetCount; /**< Holds the count of worksheets. */
        unsigned int m_chartsheetCount; /**< Holds the count of chartsheets. */

        XMLNode *m_definedNames; /**< Pointer to root node of defined names in the workbook. */

        std::unique_ptr<XLRelationships> m_relationships; /**< pointer to the XLRelationships object for workbook. */
        mutable std::unique_ptr<XLSharedStrings> m_sharedStrings; /**< Pointer to the XLSharedStrings object. */
        std::unique_ptr<XLStyles> m_styles; /**< Pointer to the XLStyles object for the workbook. */
    };
}

#endif //OPENXL_XLWORKBOOK_H

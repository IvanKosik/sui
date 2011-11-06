/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010 OSTIS

OSTIS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OSTIS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OSTIS.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------
*/


#ifndef GWFOBJECTINFOREADER_H_
#define GWFOBJECTINFOREADER_H_

#include <QDomDocument>
#include <QString>
#include <QList>
#include <QVector>
#include <QPointF>
#include <QMap>

class SCgObjectInfo;

//! Reads and stores SCgObjectInfo structures from QDomDocument.
//! NOTE: only *.gwf files are supported.
class GwfObjectInfoReader
{
public:
    typedef QList<SCgObjectInfo*>       ObjectInfoList;
    typedef QMap<int, ObjectInfoList>   TypeToObjectsMap;

    /*! Construct reader for gwf files.
     * @note It always control all read data. That means, when you delete reader. It destroy
     * all information about objects and free allocated memory.
     */
    explicit GwfObjectInfoReader();

    virtual ~GwfObjectInfoReader();

    /*! Reads info from specified document @p document.
     * @param device Pointer to IODevice for data reading
     * @return If there are no any errors during read, then return true; otherwise return false.
     * @see lastError().
     * @note this method must be called before any access to elements.
     */
    bool read(QIODevice *device);

    //! @return Last error message
    const QString& lastError() const
    {
        return mLastError;
    }

    /**
     * \defgroup accessFunctions Access Functions
     * @{
     */
    const TypeToObjectsMap& objectsInfo() const
    {
        return mObjectsInfo;
    }

    /**@}*/


private:
    typedef QMap<QString, QString> GWFType2TypeAliasMap;
    //! Map for mapping gwf types to types alias
    GWFType2TypeAliasMap mGWFType2TypeAlias;

    void createTypesMap();

    //! hold all read object info
    TypeToObjectsMap mObjectsInfo;

    /**
     * \defgroup parseF Parse Functions
     * @{
     */
    bool parseObject(const QDomElement& element, SCgObjectInfo* info);
    bool parseNode(const QDomElement& element);
    bool parsePair(const QDomElement &element);
    //deprecated arc format parser
    bool parseArc(const QDomElement &element);
    bool parseBus(const QDomElement &element);
    bool parseContour(const QDomElement &element);
    /**@}*/

    /*! Gets string value of attribute
      @param element Element to get attribute value from.
      @param attribute Attribute name.
      @param result Reference to result receiver.

      @return If value got normally, then return true, else - false
      */
    bool getAttributeString(const QDomElement &element, QString attribute, QString &result);

    /*! Gets float value of attribute
      @param element Element to get attribute value from.
      @param attribute Attribute name.
      @param result Reference to result receiver.

      @return If value got normally, then return true, else - false
      */
    bool getAttributeDouble(const QDomElement &element, QString attribute, double &result);

    /*! Gets int value of attribute
      @param element Element to get attribute value from.
      @param attribute Attribute name.
      @param result Reference to result receiver.

      @return If value got normally, then return true, else - false
      */
    bool getAttributeInt(const QDomElement &element, QString attribute, int &result);

    /*! Gets point for a line object
      @param element Element to get points from.
      @param result Reference for a point vector to write results.

      @return If points got normally, then return true, else - false.
      */
    bool getElementPoints(const QDomElement &element, QVector<QPointF> &result);

    /*! Generates last error message for non existing attribute error.
      @param element Element tag name.
      @param attribute Attribute name.
      */
    void errorHaventAttribute(QString element, QString attribute);

    /*! Generates last error message for error in float value parsing
      @param element Element tag name.
      @param attribute Attribute name.
      */
    void errorFloatParse(QString element, QString attribute);

    /*! Generates last error message for node without content tag
      @param element Element tag name
      */
    void errorHaventContent(QString element);

    /*! Generates last error message for unknown element type error.
      @param element Element tag name.
      @param type Type value.
      */
    void errorUnknownElementType(QString element, QString type);

    //! Deletes all read info.
    void del();

    QString mLastError;

};

#endif /* GWFOBJECTINFOREADER_H_ */

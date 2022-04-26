#include "textrainput.h"
#include <strstream>
/************************************************************************
** TInputInteger
**
**	Accepts signed integer inputs.  Also accepts hexadecimal numbers
** if expressed in the format "0x000..."
**
*************************************************************************/

//const char* const TInputInteger::name = "TInputInteger";

TInputInteger::TInputInteger
(
    const TRect& bounds,		// rectangle for integer's input-line
    int imaxLen,			// maximum length to use for buffer
    const Range& code,			// range of internal representation
    char* formatstring,			// desired display format
    int mapped,				// should remapping be performed?
    const Range& user			// range of user's representation
) :
    TExtended(bounds, imaxLen, code, mapped, user)
{
    //memset()
    format = formatstring;
}

ushort TInputInteger::dataSize()
{
    return sizeof(int);
}

double TInputInteger::getValue()
{
    return Value;
}

void TInputInteger::setValue (double value)
{
    Value = value;
}

void TInputInteger::updateValue()
{
    setData(&Value);
}


void TInputInteger::getData
(
    void* rec
)
{
    char buffer[intBufSize];
    long temp;

    temp = strtol(data, NULL, 0);	// convert based only on input
    if (temp > 65536L || temp < -32768L)
        temp = 65536L;
    Value = (int)temp;
    sprintf(buffer, (format == NULL) ? "%d" : format, Value);
    strnset(data, '\0', maxLen);
    strncpy(data, buffer, maxLen);
    data[maxLen] = EOS;
    drawView();				// do we really need this???
    mapToCode();			// perhaps convert the Value
    memcpy(rec, &Value, sizeof(Value));
}


void TInputInteger::setData
(
    void* rec
)
{
    char buffer[intBufSize];		// temporary buffer

    memcpy(&Value, rec, sizeof(Value));	// copy integer to value
    mapToUser();			// perhaps convert the Value
    sprintf(buffer, (format == NULL) ? "%d" : format, Value);
    strnset(data, '\0', maxLen);	// clear the data buffer
    strncpy(data, buffer, maxLen);	// copy converted number to buffer
    data[maxLen] = EOS;			// guarantee the terminating null
    selectAll(True);			// select the whole field
}


Boolean
TInputInteger::valid
(
    ushort command
)
{
    int value;
    Boolean ok;
    char msg[80];
    std::ostrstream os(msg, 80);

    ok = True;
    if ((command != cmCancel) && (command != cmValid))
    {
        if (strlen(data) == 0)
            strcpy(data, "0");

        value = (int)strtol(data, NULL, 0);
        if (value < userMin || value > userMax)
        {
            select();
            os << "Number outside range " << userMin
                << ".." << userMax << std::ends;
            messageBox(os.str(), mfError + mfOKButton);
            selectAll(True);
            ok = False;
        }
    }
    if (ok)
        return TInputLine::valid(command);
    else
        return False;
}


//void
//TInputInteger::write
//(
//    opstream& os
//)
//{
//    TInputLine::write(os);
//    os << userMin;
//    os << userMax;
//
//}
//
//void*
//TInputInteger::read
//(
//    ipstream& is
//)
//{
//    TInputLine::read(is);
//    is >> userMin;
//    is >> userMax;
//    return this;
//}
//
//TStreamable*
//TInputInteger::build()
//{
//    return new TInputInteger(streamableInit);
//}
//
//
//TStreamableClass
//RInputInteger
//(
//    TInputInteger::name,
//    TInputInteger::build,
//    __DELTA(TInputInteger)
//);


/************************************************************************
** TInputFloat
*************************************************************************/

//const char* const TInputFloat::name = "TInputFloat";
/*
TInputFloat::TInputFloat
(
    const TRect& bounds,		// rectangle for Float's input-line
    int fmaxLen,			// maximum length to use for buffer
    const Range& code,			// range of internal representation
    char* formatstring,			// desired display format
    int mapped,				// should remapping be performed?
    const Range& user			// range of user's representation
) :
    TExtended(bounds, fmaxLen, code, formatstring, mapped, user)
{
    format = formatstring;
}


ushort
TInputFloat::dataSize()
{
    return sizeof(double);
}


double
TInputFloat::getValue()
{
    return Value;
}


void
TInputFloat::putValue
(
    double value
)
{
    Value = value;
}


void
TInputFloat::updateValue()
{
    setData(&Value);
}


void
TInputFloat::getData
(
    void* rec
)
{
    char buffer[floatBufSize];

    Value = atof(data);
    sprintf(buffer, (format == NULL) ? "%g" : format, Value);
    strnset(data, '\0', maxLen);
    strncpy(data, buffer, maxLen);
    data[maxLen] = EOS;
    drawView();				// do we really need this???
    mapToCode();			// perhaps convert the Value
    memcpy(rec, &Value, sizeof(Value));
}


void
TInputFloat::setData
(
    void* rec
)
{
    char buffer[floatBufSize];

    memcpy(&Value, rec, sizeof(Value));
    mapToUser();			// perhaps convert the Value
    sprintf(buffer, (format == NULL) ? "%g" : format, Value);
    strnset(data, '\0', maxLen);
    strncpy(data, buffer, maxLen);
    data[maxLen] = EOS;
    selectAll(True);
}


Boolean
TInputFloat::valid
(
    ushort command
)
{
    double value;
    Boolean ok;
    char msg[80];
    std::ostrstream os(msg, 80);

    ok = True;
    if ((command != cmCancel) && (command != cmValid))
    {
        if (strlen(data) == 0)
            strcpy(data, "0");
        value = atof(data);
        if (value < userMin || value > userMax)
        {
            select();
            os << "Number outside range " << userMin
                << ".." << userMax << std::ends;
            messageBox(os.str(), mfError + mfOKButton);
            selectAll(True);
            ok = False;
        }
    }
    if (ok)
        return TInputLine::valid(command);
    else
        return False;
}
*/

//void
//TInputFloat::write
//(
//    opstream& os
//)
//{
//    TInputLine::write(os);
//    os << userMin;
//    os << userMax;
//}
//
//void*
//TInputFloat::read
//(
//    ipstream& is
//)
//{
//    TInputLine::read(is);
//    is >> userMin;
//    is >> userMax;
//    return this;
//}
//
//TStreamable*
//TInputFloat::build()
//{
//    return new TInputFloat(streamableInit);
//}



/************************************************************************
** TInputLong
**
**	This code is only reformatted and very slightly modified from
** BC\TVISION\DEMOS\FIELDS.CPP.
**
*************************************************************************/

//const char* const TInputLong::name = "TInputLong";
/*
TInputLong::TInputLong
(
    const TRect& bounds,		// rectangle for Long display
    int lmaxLen,			// length of buffer
    const Range& code,			// range of internal representation
    char* formatstring,			// desired display format
    int mapped,				// should remapping be performed?
    const Range& user			// range of user's representation
) :
    TExtended(bounds, lmaxLen, code, formatstring, mapped, user)
{
    format = formatstring;
}


ushort
TInputLong::dataSize()
{
    return sizeof(long);
}


double
TInputLong::getValue()
{
    return (double)Value;
}


void
TInputLong::updateValue()
{
    setData(&Value);
}


void
TInputLong::putValue
(
    double value
)
{
    value = floor(value + 0.5);		// round up number (cast can't do it)
    Value = (long)value;
}


void
TInputLong::getData
(
    void* rec
)
{
    char buffer[longBufSize];

    Value = strtol(data, NULL, 0);	// convert based only on input
    sprintf(buffer, (format == NULL) ? "%l" : format, Value);
    strnset(data, '\0', maxLen);
    strncpy(data, buffer, maxLen);
    data[maxLen] = EOS;
    drawView();				// do we really need this???
    mapToCode();			// perhaps convert the Value
    memcpy(rec, &Value, sizeof(Value));
}


void
TInputLong::setData
(
    void* rec
)
{
    char buffer[longBufSize];		// temporary buffer

    memcpy(&Value, rec, sizeof(Value));	// copy integer to value
    mapToUser();			// perhaps convert the Value
    sprintf(buffer, (format == NULL) ? "%l" : format, Value);
    strnset(data, '\0', maxLen);	// clear the data buffer
    strncpy(data, buffer, maxLen);	// copy converted number to buffer
    data[maxLen] = EOS;			// guarantee the terminating null
    selectAll(True);			// select the whole field
}


Boolean
TInputLong::valid
(
    ushort command
)
{
    long value;
    Boolean ok;
    char msg[80];
    std::ostrstream os(msg, 80);

    ok = True;
    if ((command != cmCancel) && (command != cmValid))
    {
        if (strlen(data) == 0)
            strcpy(data, "0");

        value = strtol(data, NULL, 0);
        if (value < userMin || value > userMax)
        {
            select();
            os << "Number outside range " << userMin
                << ".." << userMax << std::ends;
            messageBox(os.str(), mfError + mfOKButton);
            selectAll(True);
            ok = False;
        }
    }
    if (ok)
        return TInputLine::valid(command);
    else
        return False;
}
*/
//void
//TInputLong::write
//(
//    opstream& os
//)
//{
//    TInputLine::write(os);
//    os << userMin;
//    os << userMax;
//
//}
//
//void*
//TInputLong::read
//(
//    ipstream& is
//)
//{
//    TInputLine::read(is);
//    is >> userMin;
//    is >> userMax;
//    return this;
//}
//
//TStreamable*
//TInputLong::build()
//{
//    return new TInputLong(streamableInit);
//}
//
//
//TStreamableClass
//RInputLong
//(
//    TInputLong::name,
//    TInputLong::build,
//    __DELTA(TInputLong)
//);
//


/************************************************************************
** TExtended::TExtended
**
**	A base class for the numeric "TInput" classes.
**
**	It allows one to specify that linear mappings will take place
** before and after the data is displayed.
**
**	We include a couple of virtual functions for linear mapping,
** in case you want to create another numeric class but are too lazy to
** worry about mapping functions.
**
*************************************************************************/

//const char* const TExtended::name = "TExtended";


TExtended::TExtended
(
    const TRect& bounds,		// rectangle for the display
    int cmaxLen,			// the length of the buffer
    const Range& code,			// range of internal representation
    //char* formatstring,			// desired display format
    int mapped,				// should remapping be performed?
    const Range& user			// range of user's representation
) :
    TInputLine(bounds, cmaxLen),	// initialize the TInputLine parts

    useMap(mapped),		// should internal mappings be use?
    codeMin(code.minimum),		// lowest internal value allowed
    codeMax(code.maximum),		// highest internal value allowed
    userMin(user.minimum),		// lowest "visible" value allowed
    userMax(user.maximum),		// highest "visible" value allowed

    muserMin(0.0),			// mouse's user-minimum
    muserMax(0.0),			// mouse's user-maximum
    mouseMin(24000),		// increase this to slow it down
    mouseMax(0),			// usually always 0 (ha ha)
    mouseSlope(0.0),			// calculated in setupMouseMapping()
    kuserMin(0.0),			// key's user-minimum
    kuserMax(0.0),			// key's user-maximum
    keyMin(0),			// usually always 0 (ha ha)
    keyMax(1000),			// increase this to slow it down
    keySlope(0.0),			// calculated in setupKeyMapping()
    yMouse(0),			// current mouse "coordinate"
    yKey(0),			// current key "coordinate"
    inControl(0)			// is mouse in private use?
{
    if (!useMap)
    {
        userMin = codeMin;		// to keep the valid()'s working
        userMax = codeMax;		// to keep the valid()'s working
    }

    /********************************************************************
    ** Prepare the internal mouse mappings for this field.  We could
    ** make them different for key versus mouse if we wanted to drive
    ** the user ape!
    *********************************************************************/

    setupMouseMapping(codeMin, codeMax);
    setupKeyMapping(codeMin, codeMax);
}


/************************************************************************
** TExtended::mapToUser()
** TExtended::mapToCode()
**
**	Implements the default, a simple linear mapping using the
** slope-intercept equation.
**
**	If useMap is set, then we must have matching calls at all times,
** so the state of the Value can be known.  When we start, doDialog()
** has just called setData(), and it calls mapToCode(), so that, after
** construction of the dialog box, all the numeric items are stored in
** their user-readable format.
**
*************************************************************************/

void
TExtended::mapToUser()
{
    codeValue = getValue();		// use virtual function, get value
    if (useMap)
    {
        double denominator;
        double slope;

        denominator = codeMax - codeMin;
        if (denominator == 0.0)
            slope = 1.0;
        else
            slope = (userMax - userMin) / (codeMax - codeMin);

        userValue = userMin + (codeValue - codeMin) * slope;
        if (userValue > userMax)
            userValue = userMax;
        else if (userValue < userMin)
            userValue = userMin;
        else if (userValue == -0.0)
            userValue = 0.0;
    }
    else
    {
        userValue = codeValue;
    }
    setValue(userValue);		// put value back in derived object
}


void
TExtended::mapToCode()
{
    userValue = getValue();		// use virtual function, get value
    if (useMap)
    {
        double denominator;
        double slope;

        denominator = userMax - userMin;
        if (denominator == 0.0)
            slope = 1.0;
        else
            slope = (codeMax - codeMin) / (userMax - userMin);

        codeValue = codeMin + (userValue - userMin) * slope;
        if (codeValue > codeMax)
            codeValue = codeMax;
        else if (codeValue < codeMin)
            codeValue = codeMin;
        else if (codeValue == -0.0)
            codeValue = 0.0;
    }
    else
    {
        codeValue = userValue;
    }
    setValue(codeValue);		// put value back in derived object
}


/************************************************************************
** TExtended::handleEvent()
**
**	Intercepts the mouse and keystrokes in order to allow some
** of these events to be used to manipulate the values of fields.
**
*************************************************************************/

void
TExtended::handleEvent
(
    TEvent& event
)
{
    /********************************************************************
    ** Handling of the Mouse
    *********************************************************************/

    if (event.what == evMouseDown)		// preempt handleEvent()
    {
        if (event.mouse.buttons == mbRightButton)//RIGHT_MOUSEBUTTON)
        {
            if (!inControl)
            {
                handleMouseControl();		// home-grown loop
                //setMousePosition		// restore cursor location
                //(
                //    event.mouse.where.x, event.mouse.where.y
                //);
            }
            clearEvent(event);			// don't let TV have it
        }
    }

    /********************************************************************
    ** Handling of events for TInputLine
    *********************************************************************/

    TInputLine::handleEvent(event);		// handle the TV stuff

    /********************************************************************
    ** Handling of the Up and Down arrow keys
    **
    **	At present, there is a problem here for integers, that is not
    ** present for the mouse handler above.  The problem is that we're
    ** re-entering the handleKeyControl() function after every arrow
    ** keystroke.  That routine retrieves the last value as shown on
    ** the screen.  If the mapping is such that the last value doesn't
    ** change appearance, the value is rounded down to the original
    ** value... so we can never change it.
    **
    **	Two solutions:  (1) implement a floating-point accumulator
    ** to store a more precise representation of the integer; (2) make
    ** handleKeyControl() handle the looping, so that another special
    ** keystroke would be required to exit it.  However, then you can't
    ** tab out of the field (as for the mouse code above) without
    ** specifically handling that yourself (yuk)!
    **
    *********************************************************************/

    if (event.what == evKeyDown)
    {
        switch (event.keyDown.keyCode)
        {
            case kbUp:
            case kbDown:

                handleKeyControl(event.keyDown.keyCode);
                clearEvent(event);
                break;

            default:

                break;
        }
    }
}

//
//TStreamableClass
//RExtended
//(
//    TExtended::name,
//    TExtended::build,
//    __DELTA(TExtended)
//);


/************************************************************************
** handleMouseControl()
**
**	Handle the Mousestroke (instead of the mouse).
**
**	This routine is entered by pressing the RIGHT mouse button.
** It is exited when the LEFT mouse button is pressed; if you try
** to use the RIGHT button for this purpose, well, no user ever
** lets go quickly enough to avoid hitting the button test!
**
**	Note that when we enter this routine, we use the current
** Value to properly position the logical cursor.
**
*************************************************************************/

void
TExtended::handleMouseControl
(
    void
)
{
  /*  int ypos, ymick;
    double value;

    //(void)readYmickey();		// establish zero mickey delta
    mapToCode();			// set Value to "code" version
    value = getValue();			// floating "code" version of Value
    yMouse = mouseMapping(value);	// obtain current position
    ypos = yMouse;			// store initial position
    inControl = 1;			// keep mouse in control
    selectAll(True);			// ensure field looks "in use"
    TMouse::hide();			// the mouse cursor confuses us
    while (inControl)
    {
        ymick = readYmickey();		// see if mouse moved any
        if (ymick != 0)			// did it move in y-dimension?
        {
            ypos += ymick;
            ypos = mouseCorrect(ypos);	// make sure it's ok
            if (ypos != yMouse)
            {
                yMouseOld = yMouse;		// save old position
                yMouse = ypos;			// save new position
            }
            value = userMouseMapping(yMouse);	// convert mouse y-value
            putValue(value);			// put back into Value
            updateValue();			// update the screen
            mapToCode();			// convert back to "code"
        }
        if (readMouseButtons() == LEFT_MOUSEBUTTON)
        {
            inControl = 0;
        }
    }
    mapToUser();			// insure it's back to user format
    while (kbhit())			// gobble up any stray keystrokes
        (void)getch();
    TMouse::show();
    selectAll(False);			// unhighlight the field*/
}


/************************************************************************
** mouseCorrect()
**
**	Makes sure the current mouse position is in the correct
** range, and returns a corrected position if so; otherwise, returns
** the position unaltered.
**
**	The test isn't quite so simple, because we invert the normal
** direction of the mouse, so that moving the cursor up increases the
** number
**
*************************************************************************/

int
TExtended::mouseCorrect
(
    int ypos
)
{
    if (mouseMin < mouseMax)
    {
        if (ypos < mouseMin)
            ypos = mouseMin;
        else if (ypos > mouseMax)
            ypos = mouseMax;
    }
    else
    {
        if (ypos > mouseMin)
            ypos = mouseMin;
        else if (ypos < mouseMax)
            ypos = mouseMax;
    }
    return ypos;
}


/************************************************************************
** handleKeyControl()
**
**	Handle the keystroke (instead of the mouse).
**
**	For safety, we retrieve the previous value, in case the mouse had
** modified it.
**
*************************************************************************/

void
TExtended::handleKeyControl
(
    int key
)
{
    double value;

    mapToCode();			// set Value to "code" version
    value = getValue();			// get the object's Value ("code")
    yKey = keyMapping(value);		// obtain current key level
    yKeyOld = yKey;			// store initial position
    if (key == kbUp)			// up-arrow key
    {
        yKey++;

    }
    else if (key == kbDown)		// down-arrow key
    {
        yKey--;
    }

    if (yKey < keyMin)
        yKey = keyMin;
    else if (yKey > keyMax)
        yKey = keyMax;
    if (yKey != yKeyOld)
    {
        yKeyOld = yKey;			// save new position
    }
    value = userKeyMapping(yKey);	// get the appropriate user value
    setValue(value);			// convert it to right data-type
    updateValue();			// update the screen ("user" format)
}


/************************************************************************
** setupMouseMapping()
**
**	Sets up the above statics for use with mouseMapping() and
** userMouseMapping() below.
**
*************************************************************************/

void
TExtended::setupMouseMapping
(
    double min,
    double max
)
{
    double denominator;
    double slope;

    denominator = (double)(mouseMax - mouseMin);
    if (denominator == 0.0)		// if bad mouse range
        slope = 0.0;			// set up so that y = y0
    else
        slope = (max - min) / denominator;
    mouseSlope = slope;
    muserMin = min;
    muserMax = max;
}


/************************************************************************
** setupKeyMapping()
**
**	Sets up the above statics for use with keyMapping() and
** userKeyMapping() below.
**
*************************************************************************/

void
TExtended::setupKeyMapping
(
    double min,
    double max
)
{
    double denominator;
    double slope;

    denominator = (double)(keyMax - keyMin);
    if (denominator == 0.0)		// if bad key range
        slope = 0.0;			// set up so that y = y0
    else
        slope = (max - min) / denominator;
    keySlope = slope;
    kuserMin = min;
    kuserMax = max;
}


/************************************************************************
** userMouseMapping()
**
**	Converts the given mouse value to the user domain.  The value is
** restricted to the range
**
**		muserMin <= uservalue <= muserMax
**
*************************************************************************/

double
TExtended::userMouseMapping
(
    int mousevalue		// current value of mouse y-mickey
)
{
    double uservalue;

    uservalue = muserMin + ((double)mousevalue - mouseMin) * mouseSlope;
    if (uservalue > muserMax)
        uservalue = muserMax;
    else if (uservalue < muserMin)
        uservalue = muserMin;
    else if (uservalue == -0.0)
        uservalue = 0.0;

    return uservalue;
}


/************************************************************************
** userKeyMapping()
**
**	Converts the given key value to the user domain.  The value is
** restricted to the range
**
**		kuserMin <= uservalue <= kuserMax
**
*************************************************************************/

double
TExtended::userKeyMapping
(
    int keyvalue		// current value of key counter
)
{
    double uservalue;

    uservalue = kuserMin + ((double)keyvalue - keyMin) * keySlope;
    if (uservalue > kuserMax)
        uservalue = kuserMax;
    else if (uservalue < kuserMin)
        uservalue = kuserMin;
    else if (uservalue == -0.0)
        uservalue = 0.0;

    return uservalue;
}


/************************************************************************
** mouseMapping()
**
**	Converts the given user value back to the corresponding
** mouse value to the user domain.  The value is restricted to the range
**
**		mouseMin <= mousevalue <= mouseMax
**
*************************************************************************/

int
TExtended::mouseMapping
(
    double uservalue		// value of numeric field
)
{
    double mousevalue;

    mousevalue = (mouseSlope != 0.0) ?
        (mouseMin + ((uservalue - muserMin) / mouseSlope)) : uservalue;
    if (mousevalue == -0.0)
        mousevalue = 0.0;
    mousevalue = floor(mousevalue + 0.5);	// round up (cast can't do it)

    return mouseCorrect((int)mousevalue);	// make sure it's ok
}


/************************************************************************
** keyMapping()
**
**	Converts the given user value back to the corresponding
** key value to the user domain.  The value is restricted to the range
**
**		keyMin <= keyvalue <= keyMax
**
*************************************************************************/

int TExtended::keyMapping(double uservalue)		// value of the numeric field
{
    double keyvalue;

    keyvalue = (keySlope != 0.0) ?
        (keyMin + ((uservalue - kuserMin) / keySlope)) : uservalue;
    if (keyvalue > keyMax)
        keyvalue = keyMax;
    else if (keyvalue < keyMin)
        keyvalue = keyMin;
    keyvalue = floor(keyvalue + 0.5);		// round up (cast can't do it)

    return (int)keyvalue;
}


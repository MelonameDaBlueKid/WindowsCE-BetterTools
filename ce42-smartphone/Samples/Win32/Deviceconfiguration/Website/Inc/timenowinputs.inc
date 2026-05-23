<%

function zeroize(digit)
    if digit < 10 then
        digit = "0" & digit
    end if
    zeroize = digit
end function

    dim MyMonth, MyDay, MyHour, MyMinute, MySecond
    MyMonth  = zeroize(Month(Now))
    MyDay    = zeroize(Day(Now))
    MyHour   = zeroize(Hour(Now))
    MyMinute = zeroize(Minute(Now))
    MySecond = zeroize(Second(Now))

%>

<input type="hidden" name="year" value="<%=Year(Now)%>">
<input type="hidden" name="month" value="<%=MyMonth%>">
<input type="hidden" name="day" value="<%=MyDay%>">
<input type="hidden" name="hour" value="<%=MyHour%>">
<input type="hidden" name="minute" value="<%=MyMinute%>">
<input type="hidden" name="second" value="<%=MySecond%>">

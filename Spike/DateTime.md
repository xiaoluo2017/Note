# DateTime
## 1. Use UTC for past events
* A DateTime object can fall into one of three different categories, the DateTime object has a property called “Kind” that represents each one of the possible categories: UTC, Unspecified and Local
* UTC: Every time you need to record, in a precise and unambiguous way
```
// Use DateTime.UtcNow instead of DateTime.Now, DateTime.Now is also not unit-testing friendly. If some portion of your code includes a call to DateTime.Now, it means that it depends on an external data source it doesn't control.
DateTime now = DateTime.UtcNow;
```

* Local: A local DateTime value only knows that it’s local in relation to the machine where it was generated.(Remember to always convert dates to UTC before performing arithmetic with them. DateTime.Now is OK to use when you just want to display the current time on your application’s screen)
```
var start = DateTime.Now; // local time
var end = DateTime.Now; // local time
var duration = end.ToUniversalTime() - start.ToUniversalTime(); // converting to UTC
```

> ref: https://blog.submain.com/4-common-datetime-mistakes-c-avoid/

## 2. Not use Utc for future local events
* Save DateTime using Local time(or DateTimeOffset) and TimeZoneInfo for future events

```
// save DateTime using Local time and TimeZoneInfo
public class Conference
{
    public int Id { get; set; }
    public string Name { get; set; }
    public string Address { get; set; }
    public LocalDateTime LocalStart { get; set; } // Local start: date/time in the specified time zone
    public string TimeZoneId { get; set; } // Time zone ID: string
    public Instant UtcStart { get; set; }
    public string TimeZoneRules { get; set; } // UTC start: derived field for convenience
}
 
// In other code... some parameters might be fields in the class.
public void UpdateUtcStart(
    Conference conference,
    IDateTimeZoneProvider latestZoneProvider)
{
    DateTimeZone newZone = latestZoneProvider[conference.TimeZoneId];
    // Preserve the local time, but with the new time zone rules
    ZonedDateTime newZonedStart = conference.LocalStart.InZoneLeniently(newZone);
 
    // Update the conference entry with the new information
    conference.UtcStart = newZonedStart.ToInstant();
    conference.TimeZoneRules = latestZoneProvider.VersionId;
}
```

```
// save DateTime using DateTimeOffset and TimeZoneInfo
// Start: 2022-07-10T09:00:00+02:00
// TimeZoneId: Europe/Amsterdam
```

> ref: https://codeblog.jonskeet.uk/2019/03/27/storing-utc-is-not-a-silver-bullet/

## 3. DateTime should be stored in the database using DateTimeOffset and a TimeZoneInfo.Id value

* Problem: When saving dateTime to the database, the type attribute information will be lost (UTC / local-> unspecified)
* Solution 1, implicit:
    * Using DateTime where you hope everyone sticks to the unwritten rule of the timezone always being UTC+0.
    * It’s a recommended practice to use UTC to record the time when an event happened. My suggestion here is to follow this advice and also to make it explicit that you’re doing so. Append the "UTC" suffix to every database column and class property that holds a UTC datetime. Instead of Created, change it to CreatedUTC and so on.

* Solution 2, explicit:
    * Using DateTimeOffset because the timezone is forced to UTC+0, don’t forget to set the TimeZoneInfo.Id value

> ref: https://stackoverflow.com/questions/4331189/datetime-vs-datetimeoffset
> ref: https://docs.microsoft.com/en-us/dotnet/api/system.datetimeoffset?view=netframework-4.7.2

## 4. Check whether the dateTime entered by the user are ambiguous or skipped times
```
TimeZoneInfo tz = TimeZoneInfo.Local; // getting the current system timezone
DateTime dateTime = GetDateTimeFromUserInput(); // or another external untrusted source

if (tz.IsAmbiguousTime(dateTime))
{
    // do something
}

if (tz.IsInvalidTime(dateTime))
{
    // do something
}

// seems good to go!
```

## 5. Create datetime in a specific time zone
```
public struct DateTimeWithZone
{
    private readonly DateTime utcDateTime;
    private readonly TimeZoneInfo timeZone;

    public DateTimeWithZone(DateTime dateTime, TimeZoneInfo timeZone)
    {
        var dateTimeUnspec = DateTime.SpecifyKind(dateTime, DateTimeKind.Unspecified);
        utcDateTime = TimeZoneInfo.ConvertTimeToUtc(dateTimeUnspec, timeZone); 
        this.timeZone = timeZone;
    }

    public DateTime UniversalTime { get { return utcDateTime; } }

    public TimeZoneInfo TimeZone { get { return timeZone; } }

    public DateTime LocalTime
    { 
        get 
        { 
            return TimeZoneInfo.ConvertTime(utcDateTime, timeZone); 
        }
    }        
}
```

```
public static DateTime GmtToPacific(DateTime dateTime)
{
    return TimeZoneInfo.ConvertTimeFromUtc(dateTime, TimeZoneInfo.FindSystemTimeZoneById("Pacific Standard Time"));
		
    // Another way
	  // return TimeZoneInfo.ConvertTimeBySystemTimeZoneId(DateTime.UtcNow, "Central Standard Time");
	
	  // In windows TimeZone Id List can see this answer: 
	  // https://stackoverflow.com/questions/14149346/what-value-should-i-pass-into-timezoneinfo-findsystemtimezonebyidstring/24460750#24460750
}
```

```
// DateTimeOffset is not associated with any time zone, it cannot possibly apply DST rules, DST is a rule of a particular time zone.
// You need also record TimeZoneInfo.
DateTimeOffset do1 = new DateTimeOffset(2008, 8, 22, 1, 0, 0, new TimeSpan(-5, 0, 0));
```
> ref: https://stackoverflow.com/questions/246498/creating-a-datetime-in-a-specific-time-zone-in-c-sharp

## 6. Leap year related
### 6.1 Check if the year is leap year
* DateTime.IsLeapYear()
```
int year = 2019; // year must be between 1 and 9999
bool isLeapYear = DateTime.IsLeapYear(year); // isLeapYear == false
```
> ref: https://www.tutorialspoint.com/datetime-isleapyear-method-in-chash


### 6.2 Calculate the current day-of-year
* There's a DateTime property named: DayOfYear
```
Console.WriteLine(DateTime.Now.DayOfYear);
```

* Or for any date:
```
var d = new DateTime(2010, 5, 30);
Console.WriteLine(d.DayOfYear);
```
> ref: https://stackoverflow.com/questions/2923193/c-sharp-how-to-calculate-the-current-day-of-year

### 6.3 Getting number of days in a month
```
int days = DateTime.DaysInMonth(year, month);
```

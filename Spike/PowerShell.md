# PowerShell
## 1. Variable
* $null
* $true
* $false
* $_

## 2. Data Structure
* array: 
```
$a = @(18, 7, 22)
a[1] # == 7
```

* hashmap:
```
$h = @{apple = "red"; orange = 18}
$h['apple'] # == red
$h.orange # == 18
$h.orange = 7
$h.orange # == 7
```

## 2. if switch for foreach while
* if
```
$var = 22
if ($var -gt 18)
{
    Write-Host "$var is greater than 18"
}
elseif ($var -lt 7)
{
    Write-Host "$var is less than 7"
}
else
{
    Write-Host "$var is between 7 and 18"
}
```

* switch
```
switch ($var)
{
    18 { Write-Host "$var is 18"; break }
    7 { Write-Host "$var is 7"; break }
    Default { Write-Host "$var is neither 18 nor 7" }
}
```

* for
```
for ($i = 1; $i -le 5; $i++)
{
    $i
}
```

* foreach
```
$numbers = @(1, 2, 3, "four")
foreach($n in $numbers)
{
    $n  
} 
```

* while
```
$x = 0
while ($x -lt 3)
{
    Write-Host "Hello World"
    $x += 1
}
```

## 3. Object
```
$version = New-Object System.Version
$version = New-Object System.Version 20, 1
$version = [System.Version]::new()
$version = [System.Version]::new(20, 1)

# conversion
[int] 1.7
[System.Version] "2.0.1.3"
```

## 4. Class
```
class MyVersion
{
    [int]$Major
    [int]$Minor
    [int]$Build
    [int]$Rev

    MyVersion() 
    { 
        $this.Major, $this.Minor, $this.Build, $this.Rev = 0
    }

    MyVersion($Major, $Minor, $Build, $Rev)
    {
        $this.Major = $Major 
        $this.Minor = $Minor
        $this.Build = $Build 
        $this.Rev = $Rev
    }
    
    [String] ToString()
    {
        return ($this.Major, $this.Minor, $this.Build, $this.Rev) -join '.'
    }

    [System.Version] Convert()
    {
        return [System.Version] $this.ToString()
    }
}

$mv1 = New-Object MyVersion
$mv2 = New-Object MyVersion 1,3,8,9

$mv1.Build
$mv2.ToString()
$mv2.Convert()
```

## 5. Enum
```
enum Animal
{
    Dog = 0
    Cat = 1
}

[Animal]::Cat -eq 1
```

## 6. Cmdlets & Pipeline
```
'you', 'me' | ForEach-Object{ "say $_" } // ForEach %
'you', 'me' | ForEach{ "say $_" } 
'you', 'me' | %{ "say $_" }

'you', 'me' | Where-Object{ $_ -match 'u' } // Where ? 
'you', 'me' | Where{ $_ -match 'u' } 
'you', 'me' | ?{ $_ -match 'u' } 
```

```
Get-ComputerInfo | Select-Object -ExpandProperty OsName // Select

'i like tea' -replace 'tea', 'coffee'
'i like tea' -replace '\s','_'

-join ('a','b','c')
'127', '0', '0', '1' -join '.'
```

## 7. Param Verbose CmdletBinding etc.
```
# WindowsVersion.psm1
function Format-WindowsVersion
{
    [CmdletBinding(SupportsShouldProcess)]

    param
    (
        [Parameter(Mandatory=$true, ValuefromPipeline=$true)]
        [String]
        $VersionString,

        [Switch]
        $ShowBuild
    )

    Process
    {
        Write-Verbose "s1"

        if ($PSCmdlet.ShouldProcess($_, "v1"))
        {
            Write-Verbose "s2"
            $version = [version] $_
        }

        if ($PSCmdlet.ShouldProcess($_, "v2"))
        {
            Write-Verbose "s3"
            $os = switch($version.Major, $version.Minor -join '.')
            {
                '10.0' { 1; break }
                '6.3' { 2; break }
                '6.2' { 3; break }
                '6.1' { 4; break }
                '6.0' { 5; break }
                '5.2' { 6; break}
                default { 7 }
            }

            if ($ShowBuild)
            {
                -join ($os, " Build ", $version.Build)
            }
            else
            {
                $os
            }
        }
    }
}

function Get-WindowsVersion
{
    Get-WmiObject -Class Win32_OperatingSystem | Select-Object -ExpandProperty Version
}
```

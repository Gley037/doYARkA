rule Android_APK
{
	meta:
		description = "APK file detected"
	strings:
		$ = "assets"
		$ = "META-INF"
		$ = "AndroidManifest.xml"
		$ = "classes.dex"
	condition:
        int16(0) == 0x4B50 and
		all of them
}

rule Minnavinet_Adware
{
	meta:
		description = "Minnavinet Adware file detected"
	strings:
		$string_a = "banner_layout"
		$string_b = "activity_adpath_sms"
		$string_c = "adpath_title_one"
		$string_d = "7291-2ec9362bd699d0cd6f53a5ca6cd"
	condition:
		int16(0) == 0x4B50 and
		all of them
}

rule SpyNetV2_APK
{
	meta:
		description = "Detected SpyNetV2 spyware sample"
	strings:
		$a = "odNotice.txt"
		$b = "camera This device has camera!"
		$c = "camera This device has Nooo camera!"
		$d = "send|1sBdBBbbBBF|K|"
		$e = "send|372|ScreamSMS|senssd"
		$f = "send|5ms5gs5annc"
		$g = "send|45CLCLCa01"
		$h = "send|999SAnd|TimeStart"
		$i = "!s!c!r!e!a!m!"
	condition:
		int16(0) == 0x4B50 and
		4 of them 
}
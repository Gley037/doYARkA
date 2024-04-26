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
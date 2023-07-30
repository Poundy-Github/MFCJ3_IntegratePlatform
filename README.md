# MFC5J3_Platform
Integrate repository for MFC5J3 Platform.

Dependencies (Maybe python libraries below need to be installed when this integrate environment first used):

	1.pip install hexrec

	2.pip install cryptography

USER MANUAL:

	1. Pull & synchronize submdule of the integrate environment (eg: git clone / git submodule update --init / git pull ).

	2. Create 01_APP in integrate environment root path INTEGRATE_BASE_PATH(specified path in 'ReleaseConfiguration.txt').

	3. Pull & synchronize submdule of the application project in APP_MAKE_BASE_PATH manually(specified path in 'ReleaseConfiguration.txt').
	
	4. Update information in ReleaseConfiguration.txt:

		RELEASE_VERSION: Release version you want to release.

		'branch' : Branch name you want to integrate.
		
	5. Run (CALL) ' release.bat + project name 'and wait for release finish(maybe 40 minites or more will be need).
		
		Example : 	'./release.bat C673' OR 'python release.py C673'    ---- release C673 project 
					'./release.bat M18 ' OR 'python release.py C673'    ---- release M18 project 

		Parameter will be used to find project related input/output path.
		If there no parameter exist for release.bat/release.py , C673 will be the default parameter.

	6. MCU_RELEASE.zip(Terminal released file) will be generated if release process succeed,else reffer to error log for more information.

NOTE:

	1. errorLogBoot.txt will store some error info of boot while boot compile error accurs.
	
	2. errorLogApp.txt will store some error info of application while application compile error accurs.
	
	2. please read ReadMe.txt file in each folder for more information.


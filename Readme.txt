#############################################################################################################
#                                                                   									    #
#               __________                                 ____  _________									#
#    _____  __ _\______   \_____ _______  ______ __________\   \/  /|_	 _| ____  ___   __    ____  __  	#
#   /     \|  |  \     ___/\__  \\_  __ \/  ___// __ \_  __ \     /   | |  / __ \|/ \\  | \\ / __ \ | \\	#
#  |  Y Y  \  |  /    |     / __ \|  | \/\___ \\  ___/|  | \/     \   | |  \ ___/||  \| |  H \ ___/ |  H	#
#  |__|_|  /____/|____|    (____  /__|  /____  >\___  >__| /___/\  \  |_|	\___ ||  || |_//  \___  |_//	#
#        \/                     \/           \/     \/           \_/		    							#
#                                                                   									    #
#  Copyright (C) 2019, Ingo Berg, Oleg Lozitsky                     									    #
#                                                                   									    #
#  Web:     http://muparserx.beltoforion.de                         									    #
#  SVN:     http://muparserx.googlecode.com/svn/trunk               									    #
#  e-mail:  muparserx@beltoforion.de                                									    #
#                                                                   									    #
#  The code contains contributions made by the following people:    									    #
#           Martin Rotter (https://github.com/martinrotter)         									    #
#           Josh Blum     (https://github.com/guruofquality)        									    #
#           Oleg Lozitsky (https://github.com/UnsureJedi)           									    #
#           and others                                              									    #
#                                                                   									    #
#  This software is distributed under the terms of the              									    #
#  BSD - Clause 2 "Simplified" or "FreeBSD" Licence (BSD-2-Clause)  									    #
#                                                                   									    #
#############################################################################################################


#########################################################################
#                                                                       #
#  Version history                                                      #
#                                                                       #
#########################################################################

V1.0.0 (20181027), forked from muparserx V4.0.7
-----------------
New features:
  - Support for loops ("Loop {Body}") 
  - C-style if-then-else ("If (Condition) {Then} {Else}")
  - Break statement ("Break") to terminate Loop body execution
  - C++-style arrays:
	Allocation: "Var1 = Array(Size)" - allocates an array of values with length "Size" and assigns it to "Var1". Var1 itself can be an array element.
	Assignment of array to another array: "Var2 = Var1" - assignment is performed by pointer, any changes to Variable2 WILL affect Variable1. If you want to copy an array - do it by iterating over the elements.
	Assignment to element "Var[0] = 3"
	Assignment to element of multidimensional array "Var[1,3] = 3" - Indices are separated by comma.
  - Multiline string "{;String}" - A string that can contain newlines without being detected as end of statement. Can be useful if you pass strings as function arguments to custom functions.

Changes:
  - TokenPtr has been replaced with std::shared_ptr
  - Added functions to control parser constants and variables: 
	SetConst()	- Set a value to an existing constant
	GetConst()	- Get a value from an existing constant
	SetVar()	- Set a value to an existing variable
	GetVar()	- Get a value from an existing variable
  - Added a demo code in Example.cpp calc() to demonstrate the above features. Type "test" in parser prompt to run it.
  		.data
txt:	.asciz "Wilhelmus van Nassouwe \n Ben ick@F5Duytsch@A3Bloedt,@O3D@O3Vaderland ghetrouwe@I3Blijf ick tot inden doet;@K3E@;3Prince van Orangi@O3\n B@U3ick vry onverveert.@I3D@O3Conin@M4an Hispangi@F3\n Heb i@H3altijt gheeert.\n\nIn Godes vre@53te leven \n Heb ick altijt betracht,@J3Daerom@B3n@Q5verdrev@=3\n Om Land, @O3Luyd ghebracht:@M3Maer Godt sal my regeren@J3Als e@93goet Instrument,@J3Dat ick sal wederkeeren@I3In mijn@;3Regiment.\n\nLijdt U,@J5 Ondersaten, \n Die oprecht z@N4van aert@L4Godt sal u niet verlaten@J3Al zijt ghy nu beswaert:@J3Die vroom@E3ghe@E3 te leven,@N3Bidt Go@43nacht ende d@:3.@L3Dat Hy my cr@M5wil gheven@M7ick u help@B3m@S3.\n\nLijf ende goed al te sam@Q3\n Heb ick u niet verschoont,@L3Mijn Broed@F3, @G3ch van Namen@Q4Hebbent u @K3k vertoont:@J3Graef Adolff is ghebleven,@L3In Vrieslandt in den Slach@M4Sijn siel@I3t eewich lev@S3\n Verw@W3t d@>3jonghst@H3d@C3.\n\nEdel @W3Hooch ghebor@W3\n Van Keyserlick@Q3stam:@H3E@N3Vorst des Rijcks vercoren,@P3Als e@T3vroom Christen-ma@M5Voor Godes W@:3t ghepreese@N5Heb ick vrij onversaecht@K4Als een helt zonder@W3ees@C3\n Mijn edel bloet gewaecht.\n\n@J5schilt ende betrouwen \n Zijt ghy, O Godt, mijn Heer.@N3Op U soo wil ick bouwen,@J3Verlaet my nimmermeer;@H3Dat ick doch vroom mag blijven@P3U dienaer t'all@73stond@I3Die tyranny verdrijven,@I7my mijn hert doorwondt.\n\nVal @23d@S6beswaren, \n End mijn vervolghers z@@3@L4M@H4Godt wilt doch bewaren@M3D@53trouw@=3dienaer@73jn:@K4at sy my niet verasschen@K3In haer@;3boos@B3moet,@H3H@E3@J3nd@V3niet @R3wassch@T3\n In mijn on@A3uldich bloet.\n\nAls David moeste vluchten \n Voor Saul d@?3tyran:@F3Soo heb ick moet@K3such@74\n Met menich edelman:@E4aer Godt heef@54m verheven,@O3Verlost uit alder noot@I4Een Coninckrijck ghe@23v@F3\n In Israel, seer groot.\n\nNa tsu@@3sal ick ontfanghen \n Van Godt, mijn Heer, dat soe@D3\n Daer na@?3 d@B3 verlanghen@L3Mijn vorstelick @F3m@T3,@J3Dat is, d@74@J3mag @V3rven@M3Met eeren, in@S5velt,@I3E@O3eeuwich rijk@H3rwerv@F3\n Als@L3n ghetrouwe helt.\n\nNiets doet my meer erbarmen \n In mijn@;3wedersp@W3,@G3Dan dat @U4siet verar@=4@K3es Conincks land@S3goet,@K4at ud de Spaengiaerts crencken@R4O edel Neerlandt soet@H4Als ick daeraen ghedencke@L4Mijn @?3l hert@S3t bloet.\n\nAls een Prins opgheset@@3\n Met mijnes heyr@63cracht,@K3Van d@U3tyr@93vermet@>3\n Heb ick@L5slach@L4w@73t,@M3Die, by Maestri@E3 begraven@N4Bevreesde mijn ghewelt;@I3M@?4ruyters sach men drav@63\n Seer moedi@I3door dat velt.\n\nSoo het den wil@73s Heer@>3\n Op die tijt had gheweest,@K3H@?3ick geern willen k@<3@63\n Van u dit swaer tempeest:@K3M@@4de He@H3van hi@Q3boven@M3Die alle dinck reg@V3t,@I7m@S3altijt moet loven@L4En heeft@C3ni@H3begeert.\n\nS@73 christlick was ghedreven \n Mijn prince@O5@K3moet,@J3Stantvastich is@J4bleven@K3Mijn hert in te@J3nspoet,@K3D@Q3Heer@O3b ick @M3bed@E3\n Van mijnes@M3rt@C3gront,@J3Dat Hy@M5 saeck wil reden@N4M@G4onschult doe@=3ircont.\n\nOorlof m@S4arme @V3apen, \n Die zijt in grooten n@63.@K3U Herder sal niet slapen,@K3Al zijt ghy nu verstroit:@K3Tot Godt wilt u begheven,@K3Sijn heylsaem woort neemt a@P6Als vrome Christen lev@K6Tsal hier haest zijn ghedaen.\n\nVoor Godt wil ick belijden \n End sijner groot@73macht,@K3Dat ick tot gheenen tijd@63@L3@<3Conin@P3heb veracht:@J4an dat i@J3Godt den Heere,@M4er hoochst@93Maje@83yt@J4Heb moeten obedieren@G4In der gh@@3chticheyt.\n"

		.cpu cortex-m0
		.text
		.align 2
		.global txt




_start:
	push {lr}
	ldr r0, =txt
	bl decode
	ldr r0, =buf
	bl print_asciz
	pop {pc}




//print_asciz function to print all characters of string
print_asciz:
	push {r5, lr}
	mov r5, r0			

loop:
	ldrb r0, [r5]		// load first character in r0	
	add r0, r0, #0		// add 0 to check in branh if its the end
	beq done			// branch to done if its the end
	bl print_char		// print the char
	add r5, r5, #1		// go to next address
	b loop				// go to beginning

done:
	pop {r5, pc}		// pop out of function


// decode function to remove markers and replace them with original text
// r0 = character
// r1 = offset
// r4 = buffer
// r5 = buffer location
decode:
	push {r4, r5, lr}
	ldr r4, =buf
	mov r1, r0			// save location of first character
	mov r5, r4			// save location of buffer in r5

decode_loop:
	ldrb r0, [r1]		// load character from address of r1 in r0			
	add r0, #0			// check if its the end of string
	beq end				// branch to done if its the end
	cmp r0, #'@'		// check if character is a marker
	beq match			// branch to marker if its a marker
	strb r0, [r5]		// store character from r0 in address of r4
	add r5, #1			// go to next position of buffer
	add r1, #1			// increase loop with 1 for the next character
	b decode_loop		// go back to beginning		

// r1 is the loop counter and at first the offset location
// r2 is the match start location of compressed text
// r0 is offset location
// r3 is the length of the match
match:
	add r1, r1, #1		// next character is offset
	ldrb r2, [r1]		// load offset in r2
	sub r2, #47			// substract 48 (0) to correct the value
	sub r2, r5, r2		// go to location in buffer of the match
	add r1, r1, #1		// next character is match length 
	ldrb r3, [r1]		// load this value ( amount to go forward ) in r3
	sub r3, #48			// substract 48 (0) to correct the value
	add r1, #1			// 
		
// r0 is the match character to write to buffer
// r2 is the location of the match in the buffer
// r3 is the length of the match
// r5 is the last location in buffer
match_loop:
	cmp r3, #0			// check if match length is 0				
	beq decode_loop		// if its the end go back to beginning						
	ldrb r0, [r2]		// load character of match in buffer in r0
	strb r0, [r5]		// store character of match in buffer 
	add r5, #1			// go to next position of buffer			
	add r2, #1			// go to next position of match
	sub r3, #1			// decrease the length of the match with 0
	b match_loop		// repeat loop

end:
	pop {r4, r5, pc}

//Buffer
.bss					
buf:
.skip 4000

class Homer3Dengine
    export loadarf, loadraw, moveobject, drawobject, camera, obj, movecamera
    type dot :
	record
	    x, y, z : real
	end record
    proc assign3d (var d : dot, x, y, z : real)
	d.x := x
	d.y := y
	d.z := z + 10
    end assign3d
    type object :
	record
	    axy, axz, ayz, cx, cy, cz : real
	    maxpoly : int
	    poly : array 1 .. 1000, 1 .. 3 of dot
	    col : array 1 .. 1000 of int
	end record
    var obj : object
    type cam :
	record
	    axy, axz, ayz, cx, cy, cz, zoom : real
	end record
    var camera : cam
    camera.cx := 0
    camera.cy := 0
    camera.cz := 0
    camera.axy := 0
    camera.axz := 0
    camera.ayz := 0
    camera.zoom := 300
    proc loadarf (filename : string)
	var file, i : int := 0
	var x1, y1, z1, x2, y2, z2, x3, y3, z3 : real
	var col : int
	open : file, filename, read
	loop
	    exit when eof (file)
	    i += 1

	    read : file, x1, y1, z1, x2, y2, z2, x3, y3, z3, col
	    assign3d (obj.poly (i, 1), x1, y1, z1)
	    assign3d (obj.poly (i, 2), x2, y2, z2)
	    assign3d (obj.poly (i, 3), x3, y3, z3)
	    obj.col (i) := col
	end loop
	obj.maxpoly := i
	for i2 : 1 .. obj.maxpoly
	    for ii : 1 .. 3
		obj.poly (i2, ii).z += 200
	    end for
	end for
	obj.axy := 0
	obj.axz := 0
	obj.ayz := 0
    end loadarf
    proc loadraw (filename : string, lines : int)
	var file : int
	var x1, y1, z1, x2, y2, z2, x3, y3, z3 : real
	open : file, filename, get
	obj.maxpoly := lines
	for i : 1 .. lines
	    get : file, x1, y1, z1, x2, y2, z2, x3, y3, z3
	    assign3d (obj.poly (i, 1), x1, y1, z1)
	    assign3d (obj.poly (i, 2), x2, y2, z2)
	    assign3d (obj.poly (i, 3), x3, y3, z3)
	end for
	for i : 1 .. obj.maxpoly
	    for ii : 1 .. 3
		obj.poly (i, ii).z += 200
	    end for
	end for
	obj.axy := 0
	obj.axz := 0
	obj.ayz := 0
    end loadraw
    proc rotate (OriginX, OriginY : real, var secondpartX, secondpartY : real, Rotaion : real)
	var tempx := (((OriginX - secondpartX) * cosd (Rotaion)) + ((OriginY - secondpartY) * sind (Rotaion)))
	var tempy := (((OriginY - secondpartY) * cosd (Rotaion)) - ((OriginX - secondpartX) * sind (Rotaion)))
	secondpartY := OriginY - tempy
	secondpartX := OriginX - tempx
    end rotate
    proc findcenter (var x, y, z : real)
	x := 0.0
	y := 0.0
	z := 0.0
	for i : 1 .. obj.maxpoly
	    for ii : 1 .. 3
		x += obj.poly (i, ii).x
		y += obj.poly (i, ii).y
		z += obj.poly (i, ii).z
	    end for
	end for
	x /= (obj.maxpoly * 3)
	y /= (obj.maxpoly * 3)
	z /= (obj.maxpoly * 3)
	%drawfilloval (round (obj.cx / (obj.cz / camera.zoom)) + 320, round (obj.cy / (obj.cz / camera.zoom)) + 200, 10, 10, 12)

    end findcenter

    proc draw3dpolygon (d1, d2, d3 : dot, c, c2 : int, filled : boolean)
	if d1.z not= 0 and d2.z not= 0 and d3.z not= 0 then
	    %    drawline (round (d1.x / (d1.z / camera.zoom)) + 320, round (d1.y / (d1.z / camera.zoom)) + 200, round (d2.x / (d2.z / camera.zoom)) + 320, round (d2.y / (d2.z / camera.zoom)) + 200, c)
	    %    drawline (round (d1.x / (d1.z / camera.zoom)) + 320, round (d1.y / (d1.z / camera.zoom)) + 200, round (d3.x / (d3.z / camera.zoom)) + 320, round (d3.y / (d3.z / camera.zoom)) + 200, c)
	    %    drawline (round (d2.x / (d2.z / camera.zoom)) + 320, round (d2.y / (d2.z / camera.zoom)) + 200, round (d3.x / (d3.z / camera.zoom)) + 320, round (d3.y / (d3.z / camera.zoom)) + 200, c)
	    %drawline (round (obj.cx / (obj.cz / camera.zoom)) + 320, round (obj.cy / (obj.cz / camera.zoom)) + 200, round (d2.x / (d2.z / camera.zoom)) + 320, round (d2.y / (d2.z / camera.zoom)) + 200, 12)
	    var xx : array 1 .. 3 of int
	    var yy : array 1 .. 3 of int
	    xx (1) := round ((d1.x - camera.cx) / ((d1.z - camera.cz) / camera.zoom)) + 320
	    xx (2) := round ((d2.x - camera.cx) / ((d2.z - camera.cz) / camera.zoom)) + 320
	    xx (3) := round ((d3.x - camera.cx) / ((d3.z - camera.cz) / camera.zoom)) + 320
	    yy (1) := round ((d1.y - camera.cy) / ((d1.z - camera.cz) / camera.zoom)) + 200
	    yy (2) := round ((d2.y - camera.cy) / ((d2.z - camera.cz) / camera.zoom)) + 200
	    yy (3) := round ((d3.y - camera.cy) / ((d3.z - camera.cz) / camera.zoom)) + 200
	    if filled then
		Draw.FillPolygon (xx, yy, 3, c)
	    end if
	    Draw.Polygon (xx, yy, 3, c2)
	end if
    end draw3dpolygon

    proc drawobject (col, col2, typ : int)
	if typ = 1 then
	    for i : 1 .. obj.maxpoly
		draw3dpolygon (obj.poly (i, 1), obj.poly (i, 2), obj.poly (i, 3), col, col2, true)
	    end for
	end if
	if typ = 2 then
	    var cc : real
	    for i : 1 .. obj.maxpoly
		cc := (obj.poly (i, 2).z + obj.poly (i, 1).z + obj.poly (i, 3).z) / 3
		draw3dpolygon (obj.poly (i, 1), obj.poly (i, 2), obj.poly (i, 3), (16 + (14 - (round ((cc / 31) mod 14)))), col2, true)
	    end for
	end if
	if typ = 3 then
	    for i : 1 .. obj.maxpoly
		draw3dpolygon (obj.poly (i, 1), obj.poly (i, 2), obj.poly (i, 3), col, col2, false)
	    end for
	end if
	if typ = 4 then
	    for i : 1 .. obj.maxpoly
		draw3dpolygon (obj.poly (i, 1), obj.poly (i, 2), obj.poly (i, 3), obj.col (i), col2, true)
	    end for
	end if
    end drawobject

    proc moveobject (s : string, d : real)
	findcenter (obj.cx, obj.cy, obj.cz)
	case s of
	    label "xy" :
		obj.axy += d
		for i : 1 .. obj.maxpoly
		    for ii : 1 .. 3
			rotate (obj.cx, obj.cy, obj.poly (i, ii).x, obj.poly (i, ii).y, d)
		    end for
		end for
	    label "xz" :
		obj.axz += d
		for i : 1 .. obj.maxpoly
		    for ii : 1 .. 3
			rotate (obj.cx, obj.cz, obj.poly (i, ii).x, obj.poly (i, ii).z, d)
		    end for
		end for
	    label "yz" :
		obj.ayz += d
		for i : 1 .. obj.maxpoly
		    for ii : 1 .. 3
			rotate (obj.cy, obj.cz, obj.poly (i, ii).y, obj.poly (i, ii).z, d)
		    end for
		end for
	    label "x" :
		for i : 1 .. obj.maxpoly
		    for ii : 1 .. 3
			obj.poly (i, ii).x += d
		    end for
		end for
	    label "y" :
		for i : 1 .. obj.maxpoly
		    for ii : 1 .. 3
			obj.poly (i, ii).y += d
		    end for
		end for
	    label "z" :
		for i : 1 .. obj.maxpoly
		    for ii : 1 .. 3
			obj.poly (i, ii).z += d
		    end for
		end for
	    label :
	end case
    end moveobject
    proc movecamera (s : string, d : real)
	case s of
	    label "xy" :
		camera.axy += d
		for i : 1 .. obj.maxpoly
		    for ii : 1 .. 3
			rotate (camera.cx, camera.cy, obj.poly (i, ii).x, obj.poly (i, ii).y, d)
		    end for
		end for
	    label "xz" :
		camera.axz += d
		for i : 1 .. obj.maxpoly
		    for ii : 1 .. 3
			rotate (camera.cx, camera.cz, obj.poly (i, ii).x, obj.poly (i, ii).z, d)
		    end for
		end for
	    label "yz" :
		camera.ayz += d
		for i : 1 .. obj.maxpoly
		    for ii : 1 .. 3
			rotate (camera.cy, camera.cz, obj.poly (i, ii).y, obj.poly (i, ii).z, d)
		    end for
		end for
	    label "x" :
		camera.cx += d
	    label "y" :
		camera.cy += d
	    label "z" :
		camera.cz += d
	    label "zoom" :
		camera.zoom += d
		if camera.zoom = 0 then
		    camera.zoom += d
		end if
	    label :
	end case
    end movecamera
end Homer3Dengine
var spike : ^Homer3Dengine
new Homer3Dengine, spike
spike -> loadarf ("spike.arf")
colorback (2)
cls
View.Set ("offscreenonly")
spike -> moveobject ("z", 300)
color (white)
loop
    locate (1, 1)
    put "Object coords :    ", spike -> obj.cx, " / ", spike -> obj.cy, " / ", spike -> obj.cz, " / "
    put "Object angles :    ", spike -> obj.axy mod 360, " / ", spike -> obj.axz mod 360, " / ", spike -> obj.ayz mod 360, " / "
    put "Camera coords :    ", spike -> camera.cx, " / ", spike -> camera.cy, " / ", spike -> camera.cz, " / "
    put "Camera angles :    ", spike -> camera.axy mod 360, " / ", spike -> camera.axz mod 360, " / ", spike -> camera.ayz mod 360, " / "
    put "Camera zoom :    ", spike -> camera.zoom, "X"
    spike -> moveobject ("xz", 1)%rotates the object in xz axis
    spike -> moveobject ("x", 1)%moves object in x axis
    spike -> movecamera ("z", -1)%moves camera in z axis
    spike -> drawobject (1, 10, 1) %draws the object with color 1 and 10 and in method 1
    View.Update
    delay (5)
    cls
end loop

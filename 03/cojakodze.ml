let l1 = 1.0;;
let l2 = 0.001;;
let krok_max = 10000000;;

type pair = { first : float ; second : float }
	;;

let func1 t y1 y2 =
	(-1.0 *. l1 *. y1) +. (l2 *. y2) +. (1.0 /. 2.0)
	;;

let func2 t y1 y2 =
	-1.0 *. l2 *. y2
	;;
	
let rk4_uklad prevu1 prevu2 prevt dt =
	let k1 = 
		let t = prevt in
		let y1 = prevu1 in
		let y2 = prevu2 in
			{ first = func1 t y1 y2 ; second = func2 t y1 y2 }
		in
	let k2 = 
		let t = prevt +. (dt /. 2.0) in
		let y1 = prevu1 +. (dt *. k1.first /. 2.0) in
		let y2 = prevu2 +. (dt *. k1.second /. 2.0) in
			{ first = func1 t y1 y2 ; second = func2 t y1 y2 }
		in
	let k3 = 
		let t = prevt +. (dt /. 2.0) in
		let y1 = prevu1 +. (dt *. k2.first /. 2.0) in
		let y2 = prevu2 +. (dt *. k2.second /. 2.0) in
			{ first = func1 t y1 y2 ; second = func2 t y1 y2 }
		in	
	let k4 = 
		let t = prevt +. dt in
		let y1 = prevu1 +. (dt *. k3.first) in
		let y2 = prevu2 +. (dt *. k3.second) in
			{ first = func1 t y1 y2 ; second = func2 t y1 y2 }
		in
	{ first = prevu1 +. (dt /. 6.0 ) *. (k1.first +. (2.0 *. k2.first) +. (2.0 *. k3.first) +. k4.first) ; second = prevu2 +. (dt /. 6.0 ) *. (k1.second +. (2.0 *. k2.second) +. (2.0 *. k3.second) +. k4.second) }
	;;

let perf_y1 t =
	let arg1 = -1.0 *. l1 *. t in
		let arg2 = -1.0 *. l2 *. t in
			let exp1 = exp arg1 in
				let exp2 = exp arg2 in
					(0.5 *. ((l1 +. l2) /. (l2 -. l1)) *. exp1) +. ((l2 /. (l1 -. l2)) *. exp2) +. (1.0 /. 2.0)
	;;
	
let perf_y2 t =
	let arg = -1.0 *. t in
		exp arg
	;;
	
let new_time s tol e dt n =
	let p1 = (s *. tol) /. e in
		let p2 = 1.0 /. n in
			(p1 ** p2) *. dt
	;;
	
let error y1 y2 n =
	(y2 -. y1) /. ((2.0 ** (n -. 1.0)) -. 1.0)
	;;
	
let min a b =
	if a < b then a else b
	;;
	
let rec zad1 n prevy s max_t tol funct dt t =
		let y1_dlugi = 
			let dt2 = 2.0 *. dt in
			funct prevy.first prevy.second t dt2
			in
			
		let y2_krotki = 
			let drugi = rk4_uklad prevy.first prevy.second t dt in
			let t2 = t +. dt in
			funct drugi.first drugi.second t2 dt
			in
			
		let erry_1 =
			let arg = error y1_dlugi.first y2_krotki.first n in
			abs_float arg
			in
			
		let erry_2 =
			let arg = error y1_dlugi.second y2_krotki.second n in
			abs_float arg
			in
			
		let new_dt = 
			let time1 = new_time s tol erry_1 dt n in
			let time2 = new_time s tol erry_2 dt n in
			min time1 time2
			in
			
		if t < max_t then
			if ((erry_1 < tol) && (erry_2 < tol))
			then
				let new_t = t +. (dt *. 2.0) in
					Printf.printf "%.8f %.8f %.8f %.8f %.8f %.8f %.8f\n" new_t dt y2_krotki.first y2_krotki.second new_dt erry_1 erry_2 ;
					zad1 n y2_krotki s max_t tol funct new_dt new_t
			else zad1 n prevy s max_t tol funct new_dt t
	;;
			
let a = zad1 5.0 { first = 0.0 ; second = 1.0 ; } 0.75 10000.0 0.01 rk4_uklad 1.0 0.0

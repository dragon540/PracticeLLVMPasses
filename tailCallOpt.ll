define i32 @sum(i32 %n) {
entry:
  %cmp = icmp eq i32 %n, 0
  br i1 %cmp, label %base, label %recurse

base:
  ret i32 0

recurse:
  %dec = sub i32 %n, 1
  %call = call i32 @sum(i32 %dec)
  ret i32 %call
}

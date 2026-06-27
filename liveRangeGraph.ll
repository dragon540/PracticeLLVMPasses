define i32 @foo(i32 %a, i32 %b) {
entry:
  %c = add i32 1, 2
  %d = add i32 3, 4
  %e = add i32 %c, %d
  %f = add i32 %a, %c
  %g = mul i32 %f, %d
  %h = add i32 %g, %e
  %i = sub i32 %h, %f
  %j = add i32 %i, %b
  %k = mul i32 %j, %e
  ret i32 %k
}

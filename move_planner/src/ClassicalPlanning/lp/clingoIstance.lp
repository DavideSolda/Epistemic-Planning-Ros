:- action(A), time(T), occurs(A,T), not executable(A,T).
action(noop).
action(pick_from_barrier(X)):-block(X).
action(pick(X, H, W)):-h(H), place(W), block(X).
action(put_on_barrier(X)):-block(X).
action(put(X, H, W)):-h(H), place(W), block(X).
causes(pick_from_barrier(X), barrier(X)):-block(X).
causes(pick_from_barrier(X), free_barrier):-block(X).
causes(pick_from_barrier(X), gripped(X)):-block(X).
causes(pick_from_barrier(X), neg(free_gripper)):-block(X).
causes(pick(X, H, W), gripped(X)):-h(H), place(W), block(X).
causes(pick(X, H, W), hight(W, (H-1))):-h(H), place(W), block(X).
causes(pick(X, H, W), neg(free_gripper)):-h(H), place(W), block(X).
causes(pick(X, H, W), neg(hight(W, H))):-h(H), place(W), block(X).
causes(pick(X, H, W), neg(on(X, Y)), T):-time(T), h(H), place(W), block(X), block(Y), holds(on(X, Y), T).
causes(pick(X, H, W), neg(top(X, W))):-h(H), place(W), block(X).
causes(pick(X, H, W), top(Y, W), T):-time(T), h(H), place(W), block(X), block(Y), holds(on(X, Y), T).
causes(put_on_barrier(X), barrier(X)):-block(X).
causes(put_on_barrier(X), free_gripper):-block(X).
causes(put_on_barrier(X), neg(free_barrier)):-block(X).
causes(put_on_barrier(X), neg(gripped(X))):-block(X).
causes(put(X, H, W), free_gripper):-h(H), place(W), block(X).
causes(put(X, H, W), hight(W, H)):-h(H), place(W), block(X).
causes(put(X, H, W), neg(gripped(X))):-h(H), place(W), block(X).
causes(put(X, H, W), neg(hight(W, (H-1)))):-h(H), place(W), block(X).
causes(put(X, H, W), neg(top(Y, W)), T):-time(T), h(H), place(W), block(X), block(Y), holds(top(Y, W), T).
causes(put(X, H, W), on(X, Y), T):-time(T), h(H), place(W), block(X), block(Y), holds(top(Y, W), T).
causes(put(X, H, W), top(X, W)):-h(H), place(W), block(X).
#const l=10.
exec(pick_from_barrier(X), barrier(X)):-block(X).
exec(pick_from_barrier(X), free_gripper):-block(X).
exec(pick(X, H, W), free_gripper):-h(H), place(W), block(X).
exec(pick(X, H, W), hight(W, H)):-h(H), place(W), block(X).
exec(pick(X, H, W), top(X, W)):-h(H), place(W), block(X).
exec(put_on_barrier(X), free_barrier):-block(X).
exec(put_on_barrier(X), gripped(X)):-block(X).
exec(put_on_barrier(X), neg(free_gripper)):-block(X).
exec(put(X, H, W), gripped(X)):-h(H), place(W), block(X).
exec(put(X, H, W), hight(W, (H-1))):-h(H), place(W), block(X).
exec(put(X, H, W), neg(free_gripper)):-h(H), place(W), block(X).
executable(A,T):- action(A), time(T), T<l, not not_executable(A,T).
finally(top(yellow, 1)).
fluent(barrier(X)):- block(X).
fluent(barrier(yellow)).
fluent(free_barrier).
fluent(free_gripper).
fluent(gripped(X)):- block(X).
fluent(hight(1, 2)).
fluent(hight(2, 1)).
fluent(hight(3, 0)).
fluent(hight(W, (H-1))):- h(H), place(W).
fluent(hight(W, H)):- h(H), place(W).
fluent(on(green, red)).
fluent(on(X, Y)):- block(X), block(Y).
fluent(top(blue, 2)).
fluent(top(green, 1)).
fluent(top(X, W)):- place(W), block(X).
fluent(top(yellow, 1)).
fluent(top(Y, W)):- place(W), block(Y).
goal(T) :- time(T), not not_ok(T).
holds(F,1):-initially(F).
holds(F):-holds(F,l).
holds(F,T+1):-opposto(F,G), T<l, holds(F,T), not holds(G,T+1).
holds(F,T+1):- T<l, executable(A,T), occurs(A,T), causes(A,F).
holds(F,T+1):- T<l, executable(A,T), occurs(A,T), causes(A,F,T).
holds(F,T+1):- T<l, occurs(A,T), causes(A,F,T).
initially(barrier(yellow)).
initially(free_gripper).
initially(hight(1, 2)).
initially(hight(2, 1)).
initially(hight(3, 0)).
initially(on(green, red)).
initially(top(blue, 2)).
initially(top(green, 1)).
#maximize { T:occurs(noop,T) }.
not_executable(A,T):- time(T), exec(A,F), not holds(F,T).
:- not goal(l).
not_occurs(A,T):- action(A), action(B), time(T), occurs(B,T), A!=B.
not_ok(T) :- time(T), finally(F), not holds(F,T).
occurs(A,T):- action(A), time(T), not goal(T), not not_occurs(A,T).
opposto(F,neg(F)):- fluent(F).
opposto(neg(F),F):- fluent(F).
#show holds/1.
#show occurs/2.
time(1..l).

;; NOTE: Assertions have been generated by update_lit_checks.py and should not be edited.

;; Check that optimizations on casts involving exact reference types work
;; correctly.

;; RUN: wasm-opt %s -all --optimize-instructions -S -o - | filecheck %s

(module
 ;; CHECK:      (func $cast-any-to-exact-none (type $0) (param $0 anyref) (result (exact nullref))
 ;; CHECK-NEXT:  (ref.cast (exact nullref)
 ;; CHECK-NEXT:   (local.get $0)
 ;; CHECK-NEXT:  )
 ;; CHECK-NEXT: )
 (func $cast-any-to-exact-none (param anyref) (result (exact nullref))
  ;; This will not be changed, but should not trigger an assertion.
  (ref.cast (exact nullref)
   (local.get 0)
  )
 )
 ;; CHECK:      (func $cast-null-to-exact-none (type $1) (result (exact nullref))
 ;; CHECK-NEXT:  (local $0 nullref)
 ;; CHECK-NEXT:  (ref.cast (exact nullref)
 ;; CHECK-NEXT:   (local.get $0)
 ;; CHECK-NEXT:  )
 ;; CHECK-NEXT: )
 (func $cast-null-to-exact-none (result (exact nullref))
  (local nullref)
  (ref.cast (exact nullref)
   (local.get 0)
  )
 )
)

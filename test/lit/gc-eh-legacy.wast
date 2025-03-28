;; NOTE: Assertions have been generated by update_lit_checks.py and should not be edited.

;; Check that pops of GC types work correctly.

;; RUN: wasm-opt -all %s -S -o - | filecheck %s

(module
  ;; CHECK:      (type $A (struct (field (mut i32))))
  (type $A (struct
    (field (mut i32))
  ))

  ;; CHECK:      (tag $tagA (type $1) (param (ref $A)))
  (tag $tagA (param (ref $A)))

  ;; CHECK:      (func $foo (type $2) (result (ref null $A))
  ;; CHECK-NEXT:  (try
  ;; CHECK-NEXT:   (do
  ;; CHECK-NEXT:    (nop)
  ;; CHECK-NEXT:   )
  ;; CHECK-NEXT:   (catch $tagA
  ;; CHECK-NEXT:    (return
  ;; CHECK-NEXT:     (pop (ref $A))
  ;; CHECK-NEXT:    )
  ;; CHECK-NEXT:   )
  ;; CHECK-NEXT:  )
  ;; CHECK-NEXT:  (ref.null none)
  ;; CHECK-NEXT: )
  (func $foo (result (ref null $A))
    (try
      (do
        (nop)
      )
      (catch $tagA
        (return
          (pop (ref $A))
        )
      )
    )
    (ref.null $A)
  )
)

;; NOTE: Assertions have been generated by update_lit_checks.py and should not be edited.
;; RUN: wasm-opt %s -all --nominal -S -o - | filecheck %s
;; RUN: wasm-opt %s -all --nominal --roundtrip -S -o - | filecheck %s

;; Check that intermediate types in subtype chains are also included in the
;; output module, even if there are no other references to those intermediate
;; types.

(module
  ;; CHECK:      (type $root (struct ))
  ;; CHECK:      (type $leaf (struct (field i32) (field i64) (field f32) (field f64)) (extends $twig))
  (type $leaf (struct i32 i64 f32 f64) (extends $twig))

  ;; CHECK:      (type $twig (struct (field i32) (field i64) (field f32)) (extends $branch))
  (type $twig (struct i32 i64 f32) (extends $branch))

  ;; CHECK:      (type $branch (struct (field i32) (field i64)) (extends $trunk))
  (type $branch (struct i32 i64) (extends $trunk))

  ;; CHECK:      (type $trunk (struct (field i32)) (extends $root))
  (type $trunk (struct i32) (extends $root))

  (type $root (struct))

  ;; CHECK:      (func $make-root (result (ref null $root))
  ;; CHECK-NEXT:  (ref.null $leaf)
  ;; CHECK-NEXT: )
  (func $make-root (result (ref null $root))
    (ref.null $leaf)
  )
)

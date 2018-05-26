(when (equal major-mode 'c++-mode)
  (setq ac-clang-cflags
        (list (concat "-I" (expand-file-name
                            (concat lds-dir "src")))))
  (ac-clang-update-cmdlineargs)
  (print ac-clang-cflags)
)


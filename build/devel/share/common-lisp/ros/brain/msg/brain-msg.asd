
(cl:in-package :asdf)

(defsystem "brain-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "hormone_msg" :depends-on ("_package_hormone_msg"))
    (:file "_package_hormone_msg" :depends-on ("_package"))
  ))
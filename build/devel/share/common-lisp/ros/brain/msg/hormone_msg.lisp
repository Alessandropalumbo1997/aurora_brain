; Auto-generated. Do not edit!


(cl:in-package brain-msg)


;//! \htmlinclude hormone_msg.msg.html

(cl:defclass <hormone_msg> (roslisp-msg-protocol:ros-message)
  ((name
    :reader name
    :initarg :name
    :type cl:string
    :initform "")
   (value
    :reader value
    :initarg :value
    :type cl:integer
    :initform 0))
)

(cl:defclass hormone_msg (<hormone_msg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <hormone_msg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'hormone_msg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name brain-msg:<hormone_msg> is deprecated: use brain-msg:hormone_msg instead.")))

(cl:ensure-generic-function 'name-val :lambda-list '(m))
(cl:defmethod name-val ((m <hormone_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader brain-msg:name-val is deprecated.  Use brain-msg:name instead.")
  (name m))

(cl:ensure-generic-function 'value-val :lambda-list '(m))
(cl:defmethod value-val ((m <hormone_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader brain-msg:value-val is deprecated.  Use brain-msg:value instead.")
  (value m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <hormone_msg>) ostream)
  "Serializes a message object of type '<hormone_msg>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'name))
  (cl:let* ((signed (cl:slot-value msg 'value)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <hormone_msg>) istream)
  "Deserializes a message object of type '<hormone_msg>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'value) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<hormone_msg>)))
  "Returns string type for a message object of type '<hormone_msg>"
  "brain/hormone_msg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'hormone_msg)))
  "Returns string type for a message object of type 'hormone_msg"
  "brain/hormone_msg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<hormone_msg>)))
  "Returns md5sum for a message object of type '<hormone_msg>"
  "65fedc7a0cbfb8db035e46194a350bf1")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'hormone_msg)))
  "Returns md5sum for a message object of type 'hormone_msg"
  "65fedc7a0cbfb8db035e46194a350bf1")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<hormone_msg>)))
  "Returns full string definition for message of type '<hormone_msg>"
  (cl:format cl:nil "string name~%int32 value~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'hormone_msg)))
  "Returns full string definition for message of type 'hormone_msg"
  (cl:format cl:nil "string name~%int32 value~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <hormone_msg>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'name))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <hormone_msg>))
  "Converts a ROS message object to a list"
  (cl:list 'hormone_msg
    (cl:cons ':name (name msg))
    (cl:cons ':value (value msg))
))

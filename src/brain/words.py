#! /usr/bin/env python

import roslib
import rospy

class Words:

    # Here we store the associations between words and concepts

    """
    Bad words are used to teach the dog to avoid certain things when he sees them or that some actions he does are bad
    """
    bad_words = [
        "cattivo",
        "cattiva",
        "no"
        "male"
    ];

    """
    Good words are used to teach the dog that certain things he sees or certain things he does are cool
    """
    good_words = [
        "buono",
        "buona",
        "si",
        "bene",
        "brava",
        "bravo"
    ];

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class test : MonoBehaviour {

	// Use this for initialization
	void Start () {
		int tikubi =  PlayerPrefs.GetInt("user_id");
        Debug.Log(tikubi);

        
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}

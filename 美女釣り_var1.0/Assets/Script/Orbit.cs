using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Orbit : MonoBehaviour {

    public float Distance = 10;

	// Use this for initialization
	void Start () {
        Cursor.visible = false;
    }
	
	// Update is called once per frame
	void Update () {
        Ray r = Camera.main.ScreenPointToRay(Input.mousePosition);
        Vector2 pos = r.GetPoint(Distance);
        transform.position = pos;
	}
}

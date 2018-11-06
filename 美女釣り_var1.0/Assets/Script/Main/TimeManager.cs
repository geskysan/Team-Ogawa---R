using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using DG.Tweening;

public class TimeManager : MonoBehaviour {

    [SerializeField] float time = 60f;
    [SerializeField] Text timeText;
	
	// Update is called once per frame
	void Update () {

        // タイム
        time -= Time.deltaTime;

        if(time <= 10)
        {
            timeText.color = Color.red;
        }

        if (time <= 0)
        {
            time = 0;
        }

        timeText.text = time.ToString("00");
    }
}
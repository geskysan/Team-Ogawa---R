using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using DG.Tweening;

public class TimeManager : MonoBehaviour {

    [SerializeField] float time = 60f;
    [SerializeField] Text timeText;

    [SerializeField] CanvasGroup m_TimeUp;
    [SerializeField] float[] m_MoveTime;

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        time -= Time.deltaTime;

        if(time <= 10)
        {
            timeText.color = Color.red;
        }

        if (time <= 0)
        {
            time = 0;
            TimeUp();
        }

        timeText.text = time.ToString("00");
    }

    void TimeUp()
    {
        Sequence seq = DOTween.Sequence()
            .Append(m_TimeUp.transform.DOLocalMoveY(0f, m_MoveTime[0]))
            .AppendInterval(m_MoveTime[1])
            .Append(m_TimeUp.transform.DOLocalMoveY(1280f, m_MoveTime[0]));
    }
}
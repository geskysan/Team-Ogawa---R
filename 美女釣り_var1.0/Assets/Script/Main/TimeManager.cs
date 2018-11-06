using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using DG.Tweening;

public class TimeManager : MonoBehaviour {

    [SerializeField] float time = 60f;
    [SerializeField] Text timeText;

    [SerializeField] CanvasGroup m_TimeUp;
    [SerializeField] float[] m_movePosY;
    [SerializeField] float[] m_MoveTime;
	
	// Update is called once per frame
	void Update () {
        var timeUp = false;

        time -= Time.deltaTime;

        if(time <= 10)
        {
            timeText.color = Color.red;
        }

        if (time <= 0)
        {
            timeUp = true;
            time = 0;
            TimeUp(timeUp);
        }

        timeText.text = time.ToString("00");
    }

    /// <summary>
    /// タイムアップ表示
    /// </summary>
    void TimeUp(bool timeUp)
    {
        var useFlag = false;

        if(timeUp && !useFlag)
        {
            useFlag = true;

            Sequence seq = DOTween.Sequence()
                .Append(m_TimeUp.transform.DOLocalMoveY(m_movePosY[0], m_MoveTime[0]))
                .AppendInterval(m_MoveTime[1])
                .Append(m_TimeUp.transform.DOLocalMoveY(m_movePosY[1], m_MoveTime[0]));
        }
    }
}
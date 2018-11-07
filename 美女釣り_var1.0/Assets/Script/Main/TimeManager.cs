using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using DG.Tweening;

public class TimeManager : MonoBehaviour {

    [SerializeField] float time = 60f;
    [SerializeField] Text timeText;

    [SerializeField] Color m_color;

    [SerializeField] CanvasGroup timeUp;
    [SerializeField] float[] m_timeUpPosY;
    [SerializeField] float m_timeUpwaitTime;

    bool m_bTimeUp = false;

    // Update is called once per frame
    void Update () {

        // タイム
        time -= Time.deltaTime;

        // 残り時間10秒で色変化
        if(time <= 10)
        {
            timeText.color = m_color;
        }

        // 時間切れでタイムアップ表示
        if (time <= 0)
        {
            time = 0;
            TimeUpMove();
        }

        timeText.text = time.ToString("00");
    }

    /// <summary>
    /// タイムアップの動き
    /// </summary>
    void TimeUpMove()
    {
        if(!m_bTimeUp)
        {
            Sequence seq = DOTween.Sequence();
            seq.Append(timeUp.transform.DOLocalMoveY(m_timeUpPosY[0], 1f))
                .AppendInterval(m_timeUpwaitTime)
                .Append(timeUp.transform.DOLocalMoveY(-m_timeUpPosY[1], 1f))
                .OnComplete(() =>
                {
                    m_bTimeUp = true;
                });
        }
    }
}
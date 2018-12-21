﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using DG.Tweening;

public class StartUpManager : MonoBehaviour {

    [SerializeField] GirlsManager m_girlsManager;

    [SerializeField] CanvasGroup m_ready, m_go;
    [SerializeField] float m_readyTime = 3f;

    public Text m_stageNameText;
    public Sprite m_background; 

    public bool m_OK = false;

	// Use this for initialization
	void Start () {

	}

    void StageName()
    {
        Sequence seq = DOTween.Sequence();

        seq.OnStart(() =>
        {

        })

        .OnComplete(() =>
        {

        });
    }

    void StartUp()
    {
        Sequence seq = DOTween.Sequence();
        seq.OnStart(() =>
        {
            // Ready,Goを透明にする
            m_ready.alpha = 0f;
            m_go.alpha = 0f;
        })
        // readyをフェードの出現
        .Append(m_ready.DOFade(1f, 1f))
        // 待機
        .AppendInterval(m_readyTime)
        // readyを非表示
        .Append(m_ready.DOFade(0f, 0.1f))
        // readyが消えるのと同時にGO表示
        .Join(m_go.DOFade(1f, 0.1f))
        // GOを少しずつ大きく
        .Join(m_go.transform.DOScale(1.5f, 1f))
        .AppendInterval(0.5f)
        .OnComplete(() =>
        {
            m_OK = true;
            this.gameObject.SetActive(false);
            m_girlsManager.GirlsStartUp();
        });
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using DG.Tweening;

public class StartUpManager : MonoBehaviour {

    [SerializeField] GirlsManager m_girlsManager;

    [SerializeField] CanvasGroup m_ready, m_go;
    [SerializeField] float m_readyTime = 3f;

    public bool m_OK = false;

	// Use this for initialization
	void Start () {
        Sequence seq = DOTween.Sequence();
        seq.OnStart(() =>
        {
            m_ready.alpha = 0f;
            m_go.alpha = 0f;
        })
        .Append(m_ready.DOFade(1f, 1f))
        .AppendInterval(m_readyTime)
        .Append(m_ready.DOFade(0f, 0.1f))
        .Join(m_go.DOFade(1f, 0.1f))
        .Join(m_go.transform.DOScale(1.5f, 1f))
        .AppendInterval(0.5f)
        .OnComplete(() =>
        {
            //m_girlsManager.GirlsStartUp();
            m_OK = true;
            this.gameObject.SetActive(false);
        });
        
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using DG.Tweening;

public class TitleControler : MonoBehaviour {

    [SerializeField]
    CanvasGroup m_tapLogo;
    [SerializeField]
    CanvasGroup m_titleLogo;

    [SerializeField] float m_scaleSize = 1.2f;
    [SerializeField] float m_scaleTime;
    [SerializeField] float m_titleFadeTime;

    [SerializeField] private float DurationSeconds;
    [SerializeField] private Ease EaseType;

    // Use this for initialization
    void Start()
    {
        Sequence seq = DOTween.Sequence()
            .OnStart(() =>
            {
                m_titleLogo.GetComponent<GameObject>();
                m_titleLogo.transform.localScale = new Vector3(0.1f, 0.1f, 0.1f);

            })
        .Append(m_titleLogo.transform.DOScale(1.0f, m_scaleTime))
        .Join(m_titleLogo.DOFade(1.0f, m_titleFadeTime))
        .Append(m_titleLogo.transform.DOScale(0.9f, 0.5f))
        .Join(m_titleLogo.transform.DORotate(new Vector3(0.0f, 0.0f, -10.0f), 1.5f))
        .OnComplete(() =>
        {
        m_titleLogo.transform.DORotate(new Vector3(0.0f, 0.0f, 10.0f), 1.5f).SetLoops(-1, LoopType.Yoyo);

        });
        // SoundScript.Instance.PlayBGM(SoundNameData.BGM_TITLE);
        m_tapLogo.DOFade(0.0f, this.DurationSeconds).SetEase(this.EaseType).SetLoops(-1, LoopType.Yoyo);
}



// Update is called once per frame
void Update () {
        if(Input.GetMouseButtonDown(0))
        {
            SceneNavigator.Instance.Change("menu");
        }
	}
}


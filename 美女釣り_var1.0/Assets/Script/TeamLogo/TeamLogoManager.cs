using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using DG.Tweening;

public class TeamLogoManager : MonoBehaviour {

    [SerializeField]
    CanvasGroup m_TeamLogo;
    [SerializeField]
    float m_fadeTime;

    // Use this for initialization
    void Start() {
        Sequence seq = DOTween.Sequence();

        seq.OnStart(() =>
        {
            m_TeamLogo.alpha = 0f;
        })
        .AppendInterval(m_fadeTime / 2f)
        .Append(m_TeamLogo.DOFade(1f, m_fadeTime))
        .AppendInterval(m_fadeTime / 2f)
        .Append(m_TeamLogo.DOFade(0f, m_fadeTime))
        .OnComplete(() =>
        {
            SceneChange();
        });

    }
	
	// Update is called once per frame
	void Update () {
		
	}

    void SceneChange()
    {
        SceneNavigator.Instance.Change("title");
    }
}

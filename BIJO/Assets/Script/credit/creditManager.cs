using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using DG.Tweening;

public class creditManager : MonoBehaviour {

    [SerializeField] CanvasGroup Logo;
    [SerializeField] GameObject creditText;

	// Use this for initialization
	void Start () {
        Sequence seq = DOTween.Sequence();
        seq.OnStart(() =>
        {
            Logo.alpha = 0f;
        })
            .AppendInterval(1f)
            .Append(Logo.DOFade(1f, 1f))
            .AppendInterval(2f)
            .Append(Logo.DOFade(0f, 1f))
            .AppendInterval(1f)
            .Append(
            creditText.gameObject.transform.DOLocalMoveY(4600.0f, 40f).SetEase(Ease.Linear))
            .Append(Logo.DOFade(1f, 1f))
            .AppendInterval(2f)
            .Append(Logo.DOFade(0f, 1f))
            .AppendInterval(1f)
            .OnComplete(() =>
            {
                //シーン移動
                SceneNavigator.Instance.Change("menu");
            });

        SoundScript.Instance.PlayBGM(SoundNameData.BGM_CREDIT);

    }
	
	// Update is called once per frame
	void Update () {
		if(Input.GetMouseButtonDown(0))
        {
            SceneNavigator.Instance.Change("menu");
        }
    }
}

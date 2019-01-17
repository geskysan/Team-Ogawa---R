using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using DG.Tweening;

public class NewScore : MonoBehaviour {

    [SerializeField] CanvasGroup _TM;
    [SerializeField] GameObject _text;
    [SerializeField] float x;

    public void TM()
    {
        Sequence seq = DOTween.Sequence();

        seq.OnStart(() =>
        {
            _TM.alpha = 0.0f;
        })
        .Append(_TM.DOFade(1f, 0.5f))
        .Append(_text.transform.DOLocalMoveX(x, 2f).SetEase(Ease.Linear))
        .Append(_TM.DOFade(0f, 0.5f));
    }

}
